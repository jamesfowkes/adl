import logging

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.devices.generic_device import GenericDevice

class AnalogOutput(GenericDevice, namedtuple("AnalogOutput", ["name", "pin", "limits"])):

	__slots__ = ()

	@property
	def setup(self):
		return "{name}.setup();".format(name=self.name)

	@property
	def sources(self):
		return ["analog-output.cpp"]

	@property
	def includes(self):
		return ["analog-output.h"]

	@property
	def declarations(self):
		if self.limits:
			return "static AnalogOutput {name} = AnalogOutput({pin}, {llow}, {lhigh});".format(
				name=self.name, pin=self.pin.number, llow=self.limits.low, lhigh=self.limits.high)
		else:
			return "static AnalogOutput {name} = AnalogOutput({pin});".format(
				name=self.name, pin=self.pin.number)
		
class AnalogOutputPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, device):
		limits = device.limits[0] if len(device.limits) else None
		return AnalogOutput(device.name, device.pins[0], limits)

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
