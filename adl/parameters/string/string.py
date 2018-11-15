import os
import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.parameters.generic_parameter import GenericParameter, GenericParamPlugin

from adl.types import Setting
from adl.types import ADLSource, ADLInclude
from adl.types import ParameterSource, ParameterInclude
from adl.types import LocalSource, LocalInclude

THIS_PATH = Path(__file__).parent

class StringParam(GenericParameter, namedtuple("StringParam", ["name", "reset_value", "length", "use_eeprom"])):

    __slots__ = ()

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

    @property
    def sources(self):
        return [
            ParameterSource(THIS_PATH, "string-param.cpp")
        ]

    @property
    def includes(self):
        return [
            ParameterInclude(THIS_PATH, "string-param.h")
        ]


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
