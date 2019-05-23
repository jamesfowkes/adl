import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from raat.parameters.generic_parameter import TemplatedParameter

from raat.types import Setting
from raat.types import RAATInclude
from raat.types import ParameterInclude
from raat import ctypes

THIS_PATH = Path(__file__).parent


class IntegerParam(
    TemplatedParameter, namedtuple("IntegerParam", ["name", "type", "init_value", "min", "max", "clip", "use_eeprom"])
):

    __slots__ = ()

    sources = ()

    includes = (
        RAATInclude("utility", "raat-util-limited-range-int.hpp"),
        ParameterInclude(THIS_PATH, "integer-param.hpp")
    )

    @property
    def setup(self):
        return "{name}.setup();".format(name=self.cname())

    @property
    def declarations(self):
        return (
                "static IntegerParam<{type}> {name} = "
                "IntegerParam<{type}>({init}, {min}, {max}, {clip}, {use_eeprom});"
            ).format(
                type=self.type.value,
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

        _type = param.settings.get("type", Setting("type", "", "int32_t"))
        _type = ctypes.get(_type.value)

        return IntegerParam(param.name,
                            param.settings.get(
                                "type", Setting("type", "", "int32_t")),
                            param.settings.get(
                                "init_value", Setting("init_value", "", "0")),
                            param.settings.get(
                                "min", Setting("min", "", _type.min)),
                            param.settings.get(
                                "max", Setting("max", "", _type.max)),
                            param.settings.get(
                                "clip", Setting("clip", "", "true")),
                            param.settings.get("use_eeprom", Setting(
                                "use_eeprom", "", "false"))
                            )

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
