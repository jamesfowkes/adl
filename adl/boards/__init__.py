import os
import logging

from pathlib import Path
from pathlib import Path
from yapsy.PluginManager import PluginManager

THIS_PATH = Path(__file__).parent

boards_plugin_manager = PluginManager()
boards_plugin_manager.setPluginPlaces([str(THIS_PATH)])
boards_plugin_manager.collectPlugins()

def activate_all():
	for plugin in boards_plugin_manager.getAllPlugins():
		logging.getLogger(__name__).info("Loaded board plugin '%s'", plugin.name)
		boards_plugin_manager.activatePluginByName(plugin.name)

def get(board, devices, parameters):
	logging.getLogger(__name__).info("Trying to load board '%s'", board.type)
	board = boards_plugin_manager.getPluginByName(board.type).plugin_object.get(board, devices, parameters)
	logging.getLogger(__name__).info("Loaded board. Devices and parameters:")
	for device in board.devices:
		logging.getLogger(__name__).info(device)

	for parameter in board.parameters:
		logging.getLogger(__name__).info(parameter)

	return board
	
def set_log_level(level):
	logging.getLogger(__name__).setLevel(level)
	for plugin in boards_plugin_manager.getAllPlugins():
		plugin.plugin_object.set_log_level(level)