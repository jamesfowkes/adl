import os
import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.parameters.generic_parameter import GenericParameter

from adl.types import Setting

THIS_PATH = Path(__file__).parent

class BooleanParam(GenericParameter, namedtuple("BooleanParam", ["name", "init_value"])):

	__slots__ = ()

	@property
	def setup(self):
		return ""

	@property
	def declarations(self):
		return "static BooleanParam {name} = BooleanParam({init});".format(
			name=self.cname(), init=self.init_value.value
		)

	@property
	def directory(self):
		return THIS_PATH

	@property
	def sources(self):
		return ["boolean-param.cpp"]

	@property
	def includes(self):
		return ["boolean-param.h"]


class BooleanPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, param):
		return BooleanParam(param.name, param.settings.get("init_value", Setting("init_value", "", "false")))

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
