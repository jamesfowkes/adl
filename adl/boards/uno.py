import os
import logging

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.boards import template_engine

class Uno(namedtuple("Uno", ["name", "baudrate", "devices", "info"])):
	__slots__ = ()

	@property
	def code(self):
		return template_engine.render("uno.template", self)

	def compile(self):
		return None

class UnoPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, board, devices):
		baudrate = board.attrs.get("baudrate", 115200)
		adl_buffer_size = board.attrs.get("adl_buffer_size", 32)
		return Uno(board.name, baudrate, devices, board.info)

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
