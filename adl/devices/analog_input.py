import logging

from collections import namedtuple

from yapsy.IPlugin import IPlugin

Pin = namedtuple("Pin", ["name", "number"])

class AnalogInput(namedtuple("AnalogInput", ["name", "pin"])):

	__slots__ = ()

	@property
	def setup(self):
		return "pinMode({}, INPUT);".format(self.pin.name.upper())

	@property
	def command_handler(self):
		return "analogRead({pin});".format(pin=self.pin.name.upper())

	@property
	def declarations(self):
		return "static const uint8_t {name} = {pin};".format(name=self.pin.name.upper(), pin=self.pin.number)

class AnalogInputPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, tree):
		name = tree.attrib["name"]
		pin_node = tree.find("pin")

		pin = Pin(pin_node.text, pin_node.attrib["number"])

		return AnalogInput(name, pin)

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
