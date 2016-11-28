import os
import logging

from yapsy.PluginManager import PluginManager

THIS_PATH = os.path.dirname(__file__)

boards_plugin_manager = PluginManager()
boards_plugin_manager.setPluginPlaces([THIS_PATH])
boards_plugin_manager.collectPlugins()

def activate_all():
	for plugin in boards_plugin_manager.getAllPlugins():
		logging.getLogger(__name__).info("Loaded board plugin '%s'", plugin.name)
		boards_plugin_manager.activatePluginByName(plugin.name)

def get(name, devices):
	logging.getLogger(__name__).info("Trying to load board '%s'", name)
	return boards_plugin_manager.getPluginByName(name).plugin_object.get(name, devices)

def set_log_level(level):
	logging.getLogger(__name__).setLevel(level)
	for plugin in boards_plugin_manager.getAllPlugins():
		plugin.plugin_object.set_log_level(level)