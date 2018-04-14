import logging
import os

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.devices.generic_device import GenericDevice

THIS_DIRECTORY = os.path.dirname(__file__)

class SparkfunSerialLCD(GenericDevice, namedtuple("SparkfunSerialLCD", ["name", "pin", "width", "lines"])):

	__slots__ = ()

	@property
	def setup(self):
		return "{name}.setup();".format(name=self.cname())

	@property
	def directory(self):
		return THIS_DIRECTORY

	@property
	def sources(self):
		return ["sparkfun-serial-lcd.cpp"]

	@property
	def includes(self):
		return ["sparkfun-serial-lcd.h"]

	@property
	def declarations(self):
		return "static SparkfunSerialLCD {name} = SparkfunSerialLCD({pin}, {width}, {lines});".format(
			name=self.cname(), pin=self.pin.value, width=self.width.value, lines=self.lines.value)

class SparkfunSerialLCDPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, device):
		width_value = device.settings["width"].value
		device.settings["width"] = device.settings["width"].update("DISPLAY_WIDTH_{}".format(width_value))
		lines_value = device.settings["lines"].value
		device.settings["lines"] = device.settings["lines"].update("DISPLAY_LINES_{}".format(lines_value))
		
		return SparkfunSerialLCD(device.name, device.settings["pin"], device.settings["width"], device.settings["lines"])

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
