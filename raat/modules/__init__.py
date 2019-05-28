import logging

from pathlib import Path

from yapsy.PluginManager import PluginManager


def get_module_logger():
    return logging.getLogger(__name__)


THIS_PATH = Path(__file__).parent

modules_plugin_manager = PluginManager()
modules_plugin_manager.setPluginPlaces([str(THIS_PATH)])
modules_plugin_manager.collectPlugins()


def activate_all():
    for plugin in modules_plugin_manager.getAllPlugins():
        logging.getLogger(__name__).info(
            "Loaded module plugin '%s'", plugin.name)
        modules_plugin_manager.activatePluginByName(plugin.name)


def get_single_module(module):
    logging.getLogger(__name__).info("Trying to load module '%s'", module.name)
    try:
        return modules_plugin_manager.getPluginByName(module.name).plugin_object.get(module)
    except AttributeError:
        get_module_logger().error("Could not load plugin '{}'".format(module.name))
        raise  # sys.exit()


def get(modules):
    return [get_single_module(module) for module in modules]


def set_log_level(level):
    logging.getLogger(__name__).setLevel(level)
    for plugin in modules_plugin_manager.getAllPlugins():
        plugin.plugin_object.set_log_level(level)
