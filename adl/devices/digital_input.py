import logging

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.devices.pin import Pin

class DigitalInput(namedtuple("DigitalInput", ["name", "pin"])):

	__slots__ = ()

	@property
	def setup(self):
		return "pinMode({}, INPUT{});".format(self.pin_name(), "_PULLUP" if self.pin.io == "pullup" else "")

	@property
	def command_handler(self):
		return """
			reply[0] = digitalRead({pin}) == HIGH ? '1' : '0';
			reply[1] = '\\0';
			return 1;
			""".format(pin=self.pin_name())

	def pin_name(self):
		return self.name.upper() + "_" + self.pin.name.upper()

	@property
	def declarations(self):
		return """
		static const uint8_t {pin_name} = {pin};
		""".format(pin_name=self.pin_name(), pin=self.pin.number)

class DigitalInputPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, device):
		return DigitalInput(device.name, device.pins[0])

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
