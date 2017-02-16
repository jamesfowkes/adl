import logging

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.devices.generic_device import GenericDevice

class DigitalOutput(GenericDevice, namedtuple("DigitalOutput", ["name", "pin"])):

	__slots__ = ()

	@property
	def setup(self):
		return "{name}.setup();".format(name=self.cname())

	@property
	def command_handler(self):
		return "return {name}.command_handler(command, reply);".format(name=self.cname())

	@property
	def sources(self):
		return ["digital-output.cpp"]

	@property
	def includes(self):
		return ["digital-output.h"]

	@property
	def declarations(self):
		return "static DigitalOutput {name} = DigitalOutput({pin});".format(
			name=self.cname(), pin=self.pin.number)

class DigitalOutputPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, device):
		return DigitalOutput(device.name, device.pins[0])

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
