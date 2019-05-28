import logging

from pathlib import Path
from yapsy.PluginManager import PluginManager

THIS_PATH = Path(__file__).parent

boards_plugin_manager = PluginManager()
boards_plugin_manager.setPluginPlaces([str(THIS_PATH)])
boards_plugin_manager.collectPlugins()


def get_module_logger():
    return logging.getLogger(__name__)


def activate_all():
    for plugin in boards_plugin_manager.getAllPlugins():
        logging.getLogger(__name__).info("Loaded board plugin '%s'", plugin.name)
        boards_plugin_manager.activatePluginByName(plugin.name)


def get(board, devices, parameters, modules):
    get_module_logger().info("Trying to load board '%s'", board.type)
    board = boards_plugin_manager.getPluginByName(board.type).plugin_object.get(board, devices, parameters, modules)
    get_module_logger().info("Loaded board. Devices, parameters and modules:")

    for device in board.devices.all:
        get_module_logger().info(device)

    for parameter in board.parameters.all:
        get_module_logger().info(parameter)

    for module in board.modules:
        get_module_logger().info(type(module).__name__)

    return board


def set_log_level(level):
    get_module_logger().setLevel(level)
    for plugin in boards_plugin_manager.getAllPlugins():
        plugin.plugin_object.set_log_level(level)
