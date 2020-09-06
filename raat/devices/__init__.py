import logging

from collections import namedtuple

from pathlib import Path

from yapsy.PluginManager import PluginManager

from raat.types import flatten, Setting


def get_module_logger():
    return logging.getLogger(__name__)


THIS_PATH = Path(__file__).parent

devices_plugin_manager = PluginManager()
devices_plugin_manager.setPluginPlaces([str(THIS_PATH)])
devices_plugin_manager.collectPlugins()

DevicesTuple = namedtuple("DevicesTuple", ["all", "single", "grouped"])


class GroupedDevices(namedtuple("GroupedDevices", ["base_device", "devices", "count"])):

    @classmethod
    def get(cls, base_device_def):
        base_device = devices_plugin_manager.getPluginByName(
            base_device_def.type).plugin_object.get(base_device_def)
        grouped_devices = get_named_grouped_devices(base_device_def)
        return cls(base_device, grouped_devices, base_device_def.count)


def activate_all():
    for plugin in devices_plugin_manager.getAllPlugins():
        logging.getLogger(__name__).info(
            "Loaded device plugin '%s'", plugin.name)
        devices_plugin_manager.activatePluginByName(plugin.name)


def get_single_device(device_def):
    get_module_logger().info(
        "Trying to load device '%s' (%s)", device_def.name, device_def.type
    )
    try:
        return devices_plugin_manager.getPluginByName(device_def.type).plugin_object.get(device_def)
    except: # noqa: disable=bare-except
        get_module_logger().error(
            "Could not load '{}' - check spelling and existence of device.".format(device_def.name)
        )
        raise


def get_named_grouped_devices(device_def):
    devices = []
    count = device_def.count
    settings = Setting.make_group(device_def.settings, count)

    for i in range(0, count):
        copied = device_def._replace(
            name="{:s}{:02d}".format(device_def.name, i))
        copied = copied._replace(settings=settings[i])
        get_module_logger().info("Trying to load device '%s' (%s)", copied.name, copied.type)
        devices.append(devices_plugin_manager.getPluginByName(
            device_def.type).plugin_object.get(copied))
    return devices


def get(device_defs):
    single_devices = [get_single_device(device_def)
                      for device_def in device_defs.single]
    grouped_device_objects = [
        GroupedDevices.get(base_device_def) for base_device_def in device_defs.grouped
    ]

    all_grouped_devices = flatten([g.devices for g in grouped_device_objects])

    return DevicesTuple(single_devices + all_grouped_devices, single_devices, grouped_device_objects)


def set_log_level(level):
    logging.getLogger(__name__).setLevel(level)
    for plugin in devices_plugin_manager.getAllPlugins():
        plugin.plugin_object.set_log_level(level)
