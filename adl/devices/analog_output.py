import logging

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.devices.generic_device import GenericDevice
from adl.types import Setting

class AnalogOutput(GenericDevice, namedtuple("AnalogOutput", ["name", "pin", "llimit", "hlimit"])):

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
		return "static AnalogOutput {name} = AnalogOutput({pin}, {llow}, {lhigh});".format(
			name=self.cname(), pin=self.pin.value, llow=self.llimit.value, lhigh=self.hlimit.value)

class AnalogOutputPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, device):
		llimit = device.settings.get("limits", Setting("llimit", "", 0))
		hlimit = device.settings.get("limits", Setting("hlimit", "", 255))
		return AnalogOutput(device.name, device.settings["pin"], llimit, hlimit)

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
