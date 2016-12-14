import logging

from collections import namedtuple

from yapsy.IPlugin import IPlugin

class DigitalOutput(namedtuple("DigitalOutput", ["name", "pin"])):

	__slots__ = ()

	@property
	def setup(self):
		return "pinMode({}, OUTPUT);".format(self.pin.name.upper())

	@property
	def command_handler(self):
		return """
			digitalWrite({pin}, command[0] == '0' ? LOW : HIGH);
			reply[0] = command[0];
			reply[1] = '\\0';
			return 1;
			""".format(pin=self.pin.name.upper())

	@property
	def declarations(self):
		return "static const uint8_t {name} = {pin};".format(name=self.pin.name.upper(), pin=self.pin.number)

class DigitalOutputPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, device):
		return DigitalOutput(device.name, device.pins[0])

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
