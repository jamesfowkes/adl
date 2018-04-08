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

def get(board, devices):
	logging.getLogger(__name__).info("Trying to load board '%s'", board.type)
	board = boards_plugin_manager.getPluginByName(board.type).plugin_object.get(board, devices)
	logging.getLogger(__name__).info("Loaded board and devices:")
	for device in board.devices:
		logging.getLogger(__name__).info(device)

	return board
	
def set_log_level(level):
	logging.getLogger(__name__).setLevel(level)
	for plugin in boards_plugin_manager.getAllPlugins():
		plugin.plugin_object.set_log_level(level)