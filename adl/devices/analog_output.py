import logging

from collections import namedtuple

from yapsy.IPlugin import IPlugin

Pin = namedtuple("Pin", ["name", "number"])

class AnalogOutput(namedtuple("AnalogOutput", ["name", "pin"])):

	__slots__ = ()

	@property
	def setup(self):
		return "pinMode({}, OUTPUT);".format(self.pin.name.upper())

	@property
	def command_handler(self):
		return """
		int value = atol(command);
		analogWrite({pin}, value);
		strcpy(reply, command);
		return strlen(command);
		""".format(pin=self.pin.name.upper())

	@property
	def declarations(self):
		return "static const uint8_t {name} = {pin};".format(name=self.pin.name.upper(), pin=self.pin.number)

class AnalogOutputPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, device):
		return AnalogOutput(device.name, device.pins[0])

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
