import logging

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.devices.generic_device import GenericDevice

class Reset(GenericDevice, namedtuple("Reset", ["name"])):

	__slots__ = ()

	@property
	def setup(self):
		return ""

	@property
	def command_handler(self):
		return """
			return {name}.command_handler(command, reply);
		""".format(name=self.cname())

	@property
	def sources(self):
		return ["reset.cpp"]

	@property
	def includes(self):
		return ["reset.h"]

	@property
	def declarations(self):
		return "static Reset {name} = Reset();".format(name=self.cname())

class ResetPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, device):
		return Reset(device.name)

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
