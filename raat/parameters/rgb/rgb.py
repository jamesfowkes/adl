import os
import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

import raat
from raat.parameters.generic_parameter import TemplatedParameter

from raat.types import Setting
from raat.types import RAATSource, RAATInclude
from raat.types import ParameterSource, ParameterInclude
from raat.types import LocalSource, LocalInclude

from raat import ctypes

THIS_PATH = Path(__file__).parent

class RGBParam(TemplatedParameter, namedtuple("RGBParam", ["name", "type", "limit", 
        "r_default", "g_default", "b_default", "clip", "use_eeprom"])):

    __slots__ = ()

    includes = (
        RAATInclude("utility", "raat-util-limited-range-int.hpp"),
        ParameterInclude(THIS_PATH, "rgb-param.hpp")
    )

    sources = ()

    @property
    def setup(self):
        return "{name}.setup();".format(name=self.cname())

    @property
    def declarations(self):
        return "static RGBParam<{type}> {name} = RGBParam<{type}>({limit}, {r_default}, {g_default}, {b_default}, {clip}, {use_eeprom});".format(
            type=self.type.value,
            name=self.cname(), limit=self.limit.value,
            r_default=self.r_default.value, g_default=self.g_default.value, b_default=self.b_default.value,
            clip=self.clip.value, use_eeprom=self.use_eeprom.value
        )

    @property
    def directory(self):
        return THIS_PATH

    @property
    def ctype(self):
        return type(self).__name__ + "<" + self.type.value + ">"
        
class RGBPlugin(IPlugin):
    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, param):

        _type = param.settings.get("type", Setting("type", "", "uint8_t"))
        _type = ctypes.get(_type.value)

        if _type.is_signed:
            raise Exception("RGB integer type cannot be signed!")

        return RGBParam(param.name, 
            param.settings.get("type", Setting("type", "", _type.name)),
            param.settings.get("limit", Setting("limit", "", str(_type.max))),
            param.settings.get("r_default", Setting("r_default", "", "0")),
            param.settings.get("g_default", Setting("g_default", "", "0")),
            param.settings.get("b_default", Setting("b_default", "", "0")),
            param.settings.get("clip", Setting("clip", "", "true")),
            param.settings.get("use_eeprom", Setting("use_eeprom", "", "false"))
        )

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
