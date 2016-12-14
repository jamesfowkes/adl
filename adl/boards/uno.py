import os
import logging

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl import template_engine
from adl.boards.serial.serial1 import Serial1

class Uno(namedtuple("Uno", ["name", "serial", "devices", "info"])):
	__slots__ = ()

	@property
	def code(self):
		return template_engine.render_board("uno.template", self)

	def compile(self):
		return None

class UnoPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, board, devices):
		baudrate = board.attrs.get("baudrate", 115200)
		serial = Serial1(baudrate)
		return Uno(board.name, serial, devices, board.info)

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
