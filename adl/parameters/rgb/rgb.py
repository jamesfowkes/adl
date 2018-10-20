import os
import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.parameters.generic_parameter import GenericParameter

from adl.types import Setting
from adl.types import ADLSource, ADLInclude
from adl.types import ParameterSource, ParameterInclude
from adl.types import LocalSource, LocalInclude

THIS_PATH = Path(__file__).parent

class RGBParam(GenericParameter, namedtuple("RGBParam", ["name", "limit", 
		"r_default", "g_default", "b_default", "clip", "use_eeprom"])):

	__slots__ = ()

	@property
	def setup(self):
		return ""

	@property
	def declarations(self):
		return "static RGBParam {name} = RGBParam({limit}, {r_default}, {g_default}, {b_default}, {clip}, {use_eeprom});".format(
			name=self.cname(), limit=self.limit.value,
			r_default=self.r_default.value, g_default=self.g_default.value, b_default=self.b_default.value,
			clip=self.clip.value, use_eeprom=self.use_eeprom.value
		)

	@property
	def directory(self):
		return THIS_PATH

	@property
	def sources(self):
		return [
			ADLSource("adl-util-limited-range-int.cpp"),
			ParameterSource(THIS_PATH, "rgb-param.cpp")
		]

	@property
	def includes(self):
		return [
			ADLInclude("adl-util-limited-range-int.h"),
			ParameterInclude(THIS_PATH, "rgb-param.h")
		]


class IntegerPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, param):
		return RGBParam(param.name, 
			param.settings.get("limit", Setting("limit", "", "255")),
			param.settings.get("r_default", Setting("r_default", "", "0")),
			param.settings.get("g_default", Setting("g_default", "", "0")),
			param.settings.get("b_default", Setting("b_default", "", "0")),
			param.settings.get("clip", Setting("clip", "", "true")),
            param.settings.get("use_eeprom", Setting("use_eeprom", "", "false"))
		)

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
