import logging
from collections import namedtuple
from pathlib import Path
from raat.types import flatten, Setting

from yapsy.PluginManager import PluginManager

THIS_PATH = Path(__file__).parent

parameters_plugin_manager = PluginManager()
parameters_plugin_manager.setPluginPlaces([str(THIS_PATH)])
parameters_plugin_manager.collectPlugins()

ParamsTuple = namedtuple("ParamsTuple", ["all", "single", "grouped"])


class GroupedParams(namedtuple("GroupedParams", ["base_param", "parameters", "count"])):

    @classmethod
    def get(cls, base_parameter_def):
        base_param = parameters_plugin_manager.getPluginByName(
            base_parameter_def.type).plugin_object.get(base_parameter_def)
        grouped_params = get_named_grouped_parameters(base_parameter_def)
        return cls(base_param, grouped_params, base_parameter_def.count)


def get_module_logger():
    return logging.getLogger(__name__)


def activate_all():
    for plugin in parameters_plugin_manager.getAllPlugins():
        get_module_logger().info("Loaded parameter plugin '%s'", plugin.name)
        parameters_plugin_manager.activatePluginByName(plugin.name)


def get_single_parameter(parameter_def):
    get_module_logger().info("Trying to load parameter '%s' (%s)",
                             parameter_def.name, parameter_def.type)
    return parameters_plugin_manager.getPluginByName(parameter_def.type).plugin_object.get(parameter_def)


def get_named_grouped_parameters(parameter_def):
    params = []
    count = parameter_def.count
    if len(parameter_def.settings):
        settings = Setting.make_group(parameter_def.settings, count)
    else:
        settings = None

    for i in range(0, count):
        copied = parameter_def._replace(
            name="{:s}{:02d}".format(parameter_def.name, i))
        if settings:
            copied = copied._replace(settings=settings[i])
        get_module_logger().info("Trying to load parameter '%s' (%s)", copied.name, copied.type)
        params.append(parameters_plugin_manager.getPluginByName(
            parameter_def.type).plugin_object.get(copied))
    return params


def get(parameter_defs):
    single_params = [get_single_parameter(
        parameter_def) for parameter_def in parameter_defs.single]
    grouped_param_objects = [
        GroupedParams.get(base_parameter_def) for base_parameter_def in parameter_defs.grouped
    ]

    all_grouped_params = flatten([g.parameters for g in grouped_param_objects])

    return ParamsTuple(single_params + all_grouped_params, single_params, grouped_param_objects)


def set_log_level(level):
    get_module_logger().setLevel(level)
    for plugin in parameters_plugin_manager.getAllPlugins():
        plugin.plugin_object.set_log_level(level)
