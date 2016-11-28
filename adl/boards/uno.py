import os
import logging

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.boards import template_engine

class Uno(namedtuple("Uno", ["name", "devices"])):
	__slots__ = ()

	@property
	def code(self):
		return template_engine.render("uno.template", self)

class UnoPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, name, devices):
		return Uno(name, devices)

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)

