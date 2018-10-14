import logging
import os

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.types import DeviceSource, DeviceInclude, LibraryInclude

from adl.devices.generic_device import GenericDevice, GenericDevicePlugin
from adl.types import Setting

THIS_PATH = Path(__file__).parent

class IR_Receiver(GenericDevice, namedtuple("IR_Receiver", ["name", "pin"])):

	__slots__ = ()

	@property
	def setup(self):
		return "{name}.setup();".format(name=self.cname())

	@property
	def directory(self):
		return THIS_PATH

	@property
	def sources(self):
		return [DeviceSource(THIS_PATH, "IR-receiver.cpp")]

	@property
	def includes(self):
		return [
			DeviceInclude(THIS_PATH, "IR-receiver.h"),
			LibraryInclude("IRremote.h")
		]

	@property
	def required_libraries(self):
		return ["IRremote"]

	@property
	def declarations(self):
		return "static IR_Receiver {name} = IR_Receiver({pin});".format(
			name=self.cname(), pin=self.pin.value)

class IR_ReceiverPlugin(IPlugin, GenericDevicePlugin):

	REQUIRED_SETTINGS = ["pin"]

	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, device):
		self.verify_settings(device)
		return IR_Receiver(device.name, device.settings["pin"])

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
