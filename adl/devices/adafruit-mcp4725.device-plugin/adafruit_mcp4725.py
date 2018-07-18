import logging
import os

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.types import LocalInclude

from adl.devices.generic_device import GenericDevice, GenericDevicePlugin
from adl.types import Setting

THIS_DIRECTORY = os.path.dirname(__file__)

class Adafruit_MCP4725(GenericDevice, namedtuple("Adafruit_MCP4725", ["name", "i2c_address"])):

	__slots__ = ()

	@property
	def setup(self):
		return "{name}.setup();".format(name=self.cname())

	@property
	def directory(self):
		return THIS_DIRECTORY

	@property
	def sources(self):
		return ["adafruit-mcp4725.cpp"]

	@property
	def includes(self):
		return [LocalInclude("adafruit-mcp4725.h")]

	@property
	def declarations(self):
		return "static Adafruit_MCP4725ADL {name} = Adafruit_MCP4725ADL({ads_type}, {multiplier});".format(
			name=self.cname(), ads_type=self.ads_type.value, multiplier=self.multiplier.value)

class Adafruit_MCP4725Plugin(IPlugin, GenericDevicePlugin):

	REQUIRED_SETTINGS = []

	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, device):
		
		if "i2c_address" in device.settings:
			if device.settings["i2c_address"].value not in [0x62, 0x63]:
				raise Exception(
					"MCP4725 i2c address should be 0x62 or 0x63 (got {})".format(device.settings["i2c_address"].value)
				)

		return Adafruit_MCP4725(device.name, device.settings.get("i2c_address", 0x62))

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
