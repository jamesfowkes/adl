import os
import logging
from collections import namedtuple
from pathlib import Path
from raat.types import flatten

from yapsy.PluginManager import PluginManager

THIS_PATH = Path(__file__).parent

parameters_plugin_manager = PluginManager()
parameters_plugin_manager.setPluginPlaces([str(THIS_PATH)])
parameters_plugin_manager.collectPlugins()

ParamsTuple = namedtuple("ParamsTuple", ["all", "single", "grouped"])

def get_module_logger():
    return logging.getLogger(__name__)

def activate_all():
    for plugin in parameters_plugin_manager.getAllPlugins():
        get_module_logger().info("Loaded parameter plugin '%s'", plugin.name)
        parameters_plugin_manager.activatePluginByName(plugin.name)

def get_single_parameter(parameter):
    get_module_logger().info("Trying to load parameter '%s' (%s)", parameter.name, parameter.type)
    return parameters_plugin_manager.getPluginByName(parameter.type).plugin_object.get(parameter)

def get_grouped_parameter(parameter):
    params = []
    count = parameter.count
    for i in range(0, count):
        copied = parameter._replace(name="{:s}{:02d}".format(parameter.name, i))
        get_module_logger().info("Trying to load parameter '%s' (%s)", copied.name, copied.type)
        params.append(parameters_plugin_manager.getPluginByName(parameter.type).plugin_object.get(copied))
    return params

def get(parameters):
    single_params = [get_single_parameter(parameter) for parameter in parameters.single]
    grouped_params = flatten([get_grouped_parameter(parameter) for parameter in parameters.grouped])
    return ParamsTuple(single_params + grouped_params, single_params, grouped_params)
    
def set_log_level(level):
    get_module_logger().setLevel(level)
    for plugin in parameters_plugin_manager.getAllPlugins():
        plugin.plugin_object.set_log_level(level)
