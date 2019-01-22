import os
import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from raat.parameters.generic_parameter import GenericParameter

from raat.types import Setting
from raat.types import RAATSource, RAATInclude
from raat.types import ParameterSource, ParameterInclude
from raat.types import LocalSource, LocalInclude

THIS_PATH = Path(__file__).parent

class IntegerParam(GenericParameter, namedtuple("IntegerParam", ["name", "init_value", "min", "max", "clip", "use_eeprom"])):

    __slots__ = ()

    sources = (
        RAATSource("utility", "raat-util-limited-range-int.cpp"),
        ParameterSource(THIS_PATH, "integer-param.cpp")
    )

    includes = (
        RAATInclude("utility", "raat-util-limited-range-int.h"),
        ParameterInclude(THIS_PATH, "integer-param.h")
    )

    @property
    def setup(self):
        return "{name}.setup();".format(name=self.cname())

    @property
    def declarations(self):
        return "static IntegerParam {name} = IntegerParam({init}, {min}, {max}, {clip}, {use_eeprom});".format(
            name=self.cname(), init=self.init_value.value,
            min=self.min.value, max=self.max.value, clip=self.clip.value,
            use_eeprom=self.use_eeprom.value
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
        return IntegerParam(param.name, 
            param.settings.get("init_value", Setting("init_value", "", "0")),
            param.settings.get("min", Setting("min", "", "INT32_MIN")),
            param.settings.get("max", Setting("max", "", "INT32_MAX")),
            param.settings.get("clip", Setting("clip", "", "true")),
            param.settings.get("use_eeprom", Setting("use_eeprom", "", "false"))
        )

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
