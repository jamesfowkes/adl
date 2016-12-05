import logging

from collections import namedtuple

from yapsy.IPlugin import IPlugin

Pin = namedtuple("Pin", ["name", "number"])

class Output(namedtuple("Output", ["name", "pin"])):

	__slots__ = ()

	@property
	def setup(self):
		return "pinMode({}, OUTPUT);".format(self.pin.name)

	@property
	def command_handler(self):
		return "digitalWrite({pin}, command[0] == '0' ? LOW : HIGH);".format(pin=self.pin.name)

	@property
	def declarations(self):
		return "static const uint8_t {name} = {pin};".format(name=self.pin.name, pin=self.pin.number)

class OutputPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, tree):
		name = tree.attrib["name"]
		pin_node = tree.find("pin")

		pin = Pin(pin_node.text, pin_node.attrib["number"])

		return Output(name, pin)

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
