import logging

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.devices.generic_device import GenericDevice
from adl.types import Setting

class AnalogOutput(GenericDevice, namedtuple("AnalogOutput", ["name", "pin", "llimit", "hlimit", "reset_level"])):

	__slots__ = ()

	@property
	def setup(self):
		return "{name}.setup();".format(name=self.cname())

	@property
	def sources(self):
		return ["analog-output.cpp"]

	@property
	def includes(self):
		return ["analog-output.h"]

	@property
	def declarations(self):
		return "static AnalogOutput {name} = AnalogOutput({pin}, {llow}, {lhigh}, {reset_level});".format(
			name=self.cname(), pin=self.pin.value, llow=self.llimit.value, lhigh=self.hlimit.value, reset_level=self.reset_level.value)

class AnalogOutputPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, device):
		llimit = device.settings.get("llimit", Setting("llimit", "", 0))
		hlimit = device.settings.get("hlimit", Setting("hlimit", "", 255))
		reset_level = device.settings.get("reset_level", Setting("reset_level", "", 0))
		return AnalogOutput(device.name, device.settings["pin"], llimit, hlimit, reset_level)

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
