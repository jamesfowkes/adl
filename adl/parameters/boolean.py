import logging

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.parameters.generic_parameter import GenericParameter

class Boolean(namedtuple("Boolean", ["name", "init_value"])):

	__slots__ = ()

	@property
	def setup(self):
		return ""

	@property
	def declarations(self):
		return "static bool {name} = {pin};".format(name=self.cname(), value=self.init_value)

class BooleanPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, param):
		return Boolean(param.name, param.init_value)

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
