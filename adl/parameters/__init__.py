import os
import logging
from pathlib import Path

from yapsy.PluginManager import PluginManager

THIS_PATH = Path(__file__).parent

parameters_plugin_manager = PluginManager()
parameters_plugin_manager.setPluginPlaces([str(THIS_PATH)])
parameters_plugin_manager.collectPlugins()

def get_module_logger():
	return logging.getLogger(__name__)

def activate_all():
	for plugin in parameters_plugin_manager.getAllPlugins():
		get_module_logger().info("Loaded parameter plugin '%s'", plugin.name)
		parameters_plugin_manager.activatePluginByName(plugin.name)

def get_single_parameter(parameter):
	get_module_logger().info("Trying to load parameter '%s' (%s)", parameter.name, parameter.type)
	return parameters_plugin_manager.getPluginByName(parameter.type).plugin_object.get(parameter)

def get(parameters):
	return [get_single_parameter(parameter) for parameter in parameters]
	
def set_log_level(level):
	get_module_logger().setLevel(level)
	for plugin in parameters_plugin_manager.getAllPlugins():
		plugin.plugin_object.set_log_level(level)
