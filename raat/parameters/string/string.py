import os
import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from raat.parameters.generic_parameter import GenericParameter, GenericParamPlugin

from raat.types import Setting
from raat.types import RAATSource, RAATInclude
from raat.types import ParameterSource, ParameterInclude
from raat.types import LocalSource, LocalInclude

THIS_PATH = Path(__file__).parent

class StringParam(GenericParameter, namedtuple("StringParam", ["name", "reset_value", "length", "use_eeprom"])):

    __slots__ = ()

    sources = (ParameterSource(THIS_PATH, "string-param.cpp"), )

    includes = (ParameterInclude(THIS_PATH, "string-param.h"), )

    @property
    def setup(self):
        return "{name}.setup();".format(name=self.cname())

    @property
    def declarations(self):
        return "static StringParam {name} = StringParam({reset_value}, {length}, {use_eeprom});".format(
            name=self.cname(), reset_value=self.reset_value.value, length=self.length.value,
            use_eeprom=self.use_eeprom.value
        )

    @property
    def directory(self):
        return THIS_PATH

class StringPlugin(IPlugin, GenericParamPlugin):

    REQUIRED_SETTINGS = ["length"]

    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, param):

        self.verify_settings(param)

        return StringParam(param.name, 
            param.settings.get("reset_value", Setting("reset_value", "", "NULL")),
            param.settings["length"],
            param.settings.get("use_eeprom", Setting("use_eeprom", "", "false"))
        )

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
