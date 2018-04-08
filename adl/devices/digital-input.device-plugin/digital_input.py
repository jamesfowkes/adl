import logging
import os

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.devices.generic_device import GenericDevice

THIS_DIRECTORY = os.path.dirname(__file__)

class DigitalInput(GenericDevice, namedtuple("DigitalInput", ["name", "pin"])):

	__slots__ = ()

	@property
	def setup(self):
		return "{name}.setup();".format(name=self.cname())

	@property
	def directory(self):
		return THIS_DIRECTORY

	@property
	def sources(self):
		return ["digital-input.cpp"]

	@property
	def includes(self):
		return ["digital-input.h"]

	@property
	def declarations(self):
		return "static DigitalInput {name} = DigitalInput({pin});".format(
			name=self.cname(), pin=self.pin.value)

class DigitalInputPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, device):
		return DigitalInput(device.name, device.settings["pin"])

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
