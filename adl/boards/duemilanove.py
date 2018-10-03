import os
import logging

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl import template_engine
from adl.boards.serial.serial0 import Serial0
from adl.boards.generic_board import GenericBoard
from adl.boards.uno import Uno

class Duemilanove(Uno, namedtuple("Duemilanove", 
	["name", "serial", "devices", "parameters", "custom_code", "settings", "info", "log_modules"])):
	__slots__ = ()

	@property
	def fqbn(self):
		return "arduino:avr:diecimila:cpu=atmega328"

class DuemilanovePlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, board, devices, parameters):
		baudrate = board.attrs.get("baudrate", 115200)
		serial = Serial0(baudrate)
		return Duemilanove(board.name, serial, devices, parameters, board.custom_code, board.settings, board.info, board.log_modules)

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
