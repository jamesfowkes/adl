import logging
import os

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.devices.generic_device import GenericDevice
from adl.types import Setting

THIS_DIRECTORY = os.path.dirname(__file__)


class AnalogOutput(GenericDevice, namedtuple("AnalogOutput", ["name", "pin", "low_limit", "high_limit", "reset_level"])):

	__slots__ = ()

	@property
	def setup(self):
		return "{name}.setup();".format(name=self.cname())

	@property
	def directory(self):
		return THIS_DIRECTORY


	@property
	def sources(self):
		return ["analog-output.cpp"]

	@property
	def includes(self):
		return ["analog-output.h"]

	@property
	def declarations(self):
		return "static AnalogOutput {name} = AnalogOutput({pin}, {llow}, {lhigh}, {reset_level});".format(
			name=self.cname(), pin=self.pin.value, llow=self.low_limit.value, lhigh=self.high_limit.value, reset_level=self.reset_level.value)

class AnalogOutputPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, device):
		low_limit = device.settings.get("low_limit", Setting("low_limit", "", 0))
		high_limit = device.settings.get("high_limit", Setting("high_limit", "", 255))
		reset_level = device.settings.get("reset_level", Setting("reset_level", "", 0))
		return AnalogOutput(device.name, device.settings["pin"], low_limit, high_limit, reset_level)

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
