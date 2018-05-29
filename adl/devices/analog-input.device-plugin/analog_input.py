import os
import logging

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.types import LibraryInclude, LocalInclude

from adl.devices.generic_device import GenericDevice

THIS_DIRECTORY = os.path.dirname(__file__)

class AnalogInput(GenericDevice, namedtuple("AnalogInput", ["name", "pin"])):

	__slots__ = ()

	@property
	def setup(self):
		return "{name}.setup();".format(name=self.cname())

	@property
	def directory(self):
		return THIS_DIRECTORY

	@property
	def sources(self):
		return ["analog-input.cpp"]

	@property
	def includes(self):
		return [LocalInclude("analog-input.h")]

	@property
	def declarations(self):
		return "static AnalogInput {name} = AnalogInput({pin});".format(
			name=self.cname(), pin=self.pin.value)

class AnalogInputPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, device):
		return AnalogInput(device.name, device.settings["pin"])

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
