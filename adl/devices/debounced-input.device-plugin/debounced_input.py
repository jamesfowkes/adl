import logging
import os

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.types import DeviceSource, DeviceInclude, LibraryInclude
from adl.devices.generic_device import GenericDevice

THIS_PATH = Path(__file__).parent

class DebouncedInput(GenericDevice, namedtuple("DebouncedInput", ["name", "pin", "debounce_time", "pullup"])):

	__slots__ = ()

	@property
	def setup(self):
		return "{name}.setup();".format(name=self.cname())

	@property
	def directory(self):
		return THIS_PATH

	@property
	def sources(self):
		return [DeviceSource(THIS_PATH, "debounced-input.cpp")]

	@property
	def includes(self):
		return [DeviceInclude(THIS_PATH, "debounced-input.h")]

	@property
	def declarations(self):
		return "static DebouncedInput {name} = DebouncedInput({pin}, {debounce_time}, {pullup});".format(
			name=self.cname(), pin=self.pin.value, debounce_time=self.debounce_time.value, pullup=self.pullup.value)

class TimedOnOffPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, device):
		return DebouncedInput(device.name, 
			device.settings["pin"], device.settings["debounce_time"], device.settings["pullup"])

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
