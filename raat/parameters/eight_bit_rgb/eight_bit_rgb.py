import os
import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

import raat
from raat.parameters.generic_parameter import GenericParameter

from raat.types import Setting
from raat.types import RAATSource, RAATInclude
from raat.types import ParameterSource, ParameterInclude
from raat.types import LocalSource, LocalInclude

THIS_PATH = Path(__file__).parent

class EightBitRGBParam(GenericParameter, namedtuple("EightBitRGBParam", ["name", "limit", 
		"r_default", "g_default", "b_default", "clip", "use_eeprom"])):

	__slots__ = ()

	includes = (
		RAATInclude("utility", "raat-util-limited-range-int.hpp"),
		ParameterInclude(THIS_PATH, "eight-bit-rgb-param.hpp")
	)

	sources = (
		RAATSource("utility", "raat-util-limited-range-int.cpp"),
		ParameterSource(THIS_PATH, "eight-bit-rgb-param.cpp")
	)

	@property
	def setup(self):
		return ""

	@property
	def declarations(self):
		return "static EightBitRGBParam {name} = EightBitRGBParam({limit}, {r_default}, {g_default}, {b_default}, {clip}, {use_eeprom});".format(
			name=self.cname(), limit=self.limit.value,
			r_default=self.r_default.value, g_default=self.g_default.value, b_default=self.b_default.value,
			clip=self.clip.value, use_eeprom=self.use_eeprom.value
		)

	@property
	def directory(self):
		return THIS_PATH

class IntegerPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, param):
		return EightBitRGBParam(param.name, 
			param.settings.get("limit", Setting("limit", "", "255")),
			param.settings.get("r_default", Setting("r_default", "", "0")),
			param.settings.get("g_default", Setting("g_default", "", "0")),
			param.settings.get("b_default", Setting("b_default", "", "0")),
			param.settings.get("clip", Setting("clip", "", "true")),
            param.settings.get("use_eeprom", Setting("use_eeprom", "", "false"))
		)

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
