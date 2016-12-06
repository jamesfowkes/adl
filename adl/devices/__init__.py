import os
import logging

from yapsy.PluginManager import PluginManager

THIS_PATH = os.path.dirname(__file__)

devices_plugin_manager = PluginManager()
devices_plugin_manager.setPluginPlaces([THIS_PATH])
devices_plugin_manager.collectPlugins()

def activate_all():
	for plugin in devices_plugin_manager.getAllPlugins():
		logging.getLogger(__name__).info("Loaded device plugin '%s'", plugin.name)
		devices_plugin_manager.activatePluginByName(plugin.name)

def get_single_device(device):
	logging.getLogger(__name__).info("Trying to load device '%s' (%s)", device.name, device.type)
	return devices_plugin_manager.getPluginByName(device.type).plugin_object.get(device)

def get(devices):
	return [get_single_device(device) for device in devices]
	
def set_log_level(level):
	logging.getLogger(__name__).setLevel(level)
	for plugin in devices_plugin_manager.getAllPlugins():
		plugin.plugin_object.set_log_level(level)