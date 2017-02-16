import logging

from collections import namedtuple

from yapsy.IPlugin import IPlugin

class Reset():

	__slots__ = ()

	@property
	def setup(self):
		return ""

	@property
	def command_handler(self):
		return """
			return s_resetter.command_handler(command, reply);
		"""

	@property
	def sources(self):
		return ["reset.cpp"]

	@property
	def includes(self):
		return ["reset.h"]

	@property
	def name(self):
		return "s_resetter"

	@property
	def declarations(self):
		return "static Reset s_resetter = Reset();"

class ResetPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, device):
		return Reset()

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
