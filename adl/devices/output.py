import logging

from collections import namedtuple

from yapsy.IPlugin import IPlugin

class Output(namedtuple("Output", ["name", "pin"])):

	__slots__ = ()

	@property
	def setup(self):
		return "pinMode({}, OUTPUT);".format(self.pin)

	@property
	def write(self, write_param):
		return "digitalWrite({pin}, {write_param} ? HIGH : LOW);".format(pin=self.Pin, write_param=write_param)

	@property
	def constants(self):
		return "digitalWrite({pin}, {write_param} ? HIGH : LOW);".format(pin=self.Pin, write_param=write_param)

class OutputPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, tree):
		name = tree.attrib["name"]
		pin = tree.find("pin").text
		return Output(name, pin)

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
