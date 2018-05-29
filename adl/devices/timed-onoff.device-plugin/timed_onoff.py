import logging
import os

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.types import LocalInclude

from adl.devices.generic_device import GenericDevice

THIS_DIRECTORY = os.path.dirname(__file__)

class TimedOnOff(GenericDevice, namedtuple("TimedOnOff", ["name", "pin", "ontime", "offtime"])):

	__slots__ = ()

	@property
	def setup(self):
		return "{name}.setup();".format(name=self.cname())

	@property
	def directory(self):
		return THIS_DIRECTORY

	@property
	def sources(self):
		return ["timed-onoff.cpp"]

	@property
	def includes(self):
		return [LocalInclude("timed-onoff.h")]

	@property
	def declarations(self):
		return "static TimedOnOff {name} = TimedOnOff({pin}, {ontime}, {offtime});".format(
			name=self.cname(), pin=self.pin.value, ontime=self.ontime.value, offtime=self.offtime.value)

class TimedOnOffPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, device):
		return TimedOnOff(device.name, device.settings["pin"], device.settings["ontime"], device.settings["offtime"])

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
