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

class IntegerParam(GenericParameter, namedtuple("IntegerParam", ["name", "type", "init_value", "min", "max", "clip", "use_eeprom"])):

    __slots__ = ()

    sources = (
        RAATSource("utility", "raat-util-limited-range-int.cpp"),
    )

    includes = (
        RAATInclude("utility", "raat-util-limited-range-int.hpp"),
        ParameterInclude(THIS_PATH, "integer-param.hpp")
    )

    @property
    def setup(self):
        return "{name}.setup();".format(name=self.cname())

    @property
    def declarations(self):
        return "static IntegerParam<{type}> {name} = IntegerParam<{type}>({init}, {min}, {max}, {clip}, {use_eeprom});".format(
            type=self.type.value,
            name=self.cname(), init=self.init_value.value,
            min=self.min.value, max=self.max.value, clip=self.clip.value,
            use_eeprom=self.use_eeprom.value
        )

    @property
    def directory(self):
        return THIS_PATH

    @property
    def ctype(self):
        return type(self).__name__ + "<" + self.type.value + ">"

class IntegerPlugin(IPlugin):
    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, param):

        _type = param.settings.get("type", Setting("type", "", "int32_t"))

        type_minimum = {
            "uint8_t" : "0",
            "int8_t" : "INT8_MIN",
            "uint16_t" : "0",
            "int16_t" : "INT16_MIN",
            "uint32_t" : "0",
            "int32_t" : "INT32_MIN",
        }.get(_type.value, "INT32_MIN")

        type_maximum = {
            "uint8_t" : "UINT8_MAX",
            "int8_t" : "INT8_MAX",
            "uint16_t" : "UINT16_MAX",
            "int16_t" : "INT16_MAX",
            "uint32_t" : "UINT32_MAX",
            "int32_t" : "INT32_MAX",
        }.get(_type.value, "INT32_MAX")

        return IntegerParam(param.name, 
            param.settings.get("type", Setting("type", "", "int32_t")),
            param.settings.get("init_value", Setting("init_value", "", "0")),
            param.settings.get("min", Setting("min", "", type_minimum)),
            param.settings.get("max", Setting("max", "", type_maximum)),
            param.settings.get("clip", Setting("clip", "", "true")),
            param.settings.get("use_eeprom", Setting("use_eeprom", "", "false"))
        )

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
