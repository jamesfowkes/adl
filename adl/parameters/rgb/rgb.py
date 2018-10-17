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

class RGBParam(GenericParameter, namedtuple("RGBParam", ["name", "init_value", "min", "max", "clip"])):

	__slots__ = ()

	@property
	def setup(self):
		return ""

	@property
	def declarations(self):
		return "static RGBParam {name} = RGBParam({init}, {min}, {max}, {clip});".format(
			name=self.cname(), init=self.init_value.value,
			min=self.min.value, max=self.max.value, clip=self.clip.value
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
			param.settings.get("init_value", Setting("init_value", "", "0")),
			param.settings.get("min", Setting("min", "", "INT32_MIN")),
			param.settings.get("max", Setting("max", "", "INT32_MAX")),
			param.settings.get("clip", Setting("clip", "", "true"))
		)

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
