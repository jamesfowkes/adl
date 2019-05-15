import os
import logging
from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from raat.parameters.generic_parameter import GenericParameter

from raat.types import Setting
from raat.types import ParameterSource, ParameterInclude

THIS_PATH = Path(__file__).parent

class BooleanParam(GenericParameter, namedtuple("BooleanParam", ["name", "init_value", "use_eeprom"])):

    __slots__ = ()

    sources = (ParameterSource(THIS_PATH, "boolean-param.cpp"), )

    includes = (ParameterInclude(THIS_PATH, "boolean-param.hpp"), )

    @property
    def setup(self):
        return ""

    @property
    def declarations(self):
        return "static BooleanParam {name} = BooleanParam({init}, {use_eeprom});".format(
            name=self.cname(), init=self.init_value.value,
            use_eeprom=self.use_eeprom.value
        )

    @property
    def directory(self):
        return THIS_PATH

class BooleanPlugin(IPlugin):
    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, param):
        return BooleanParam(param.name,
            param.settings.get("init_value", Setting("init_value", "", "false")),
            param.settings.get("use_eeprom", Setting("use_eeprom", "", "false"))
        )
        
    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
