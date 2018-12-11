import logging
import os

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.types import DeviceSource, DeviceInclude, LibraryInclude

from adl.devices.generic_device import GenericDevice, GenericDevicePlugin
from adl.types import Setting

THIS_PATH = Path(__file__).parent

class MAX7219(GenericDevice, namedtuple("MAX7219", ["name", "cs_pin", "data_pin", "dclk_pin"])):

    __slots__ = ()

    sources = (DeviceSource(THIS_PATH, "MAX7219.cpp"), )

    includes = (DeviceInclude(THIS_PATH, "MAX7219.h"), )


    @property
    def setup(self):
        return "{name}.setup();".format(name=self.cname())

    @property
    def directory(self):
        return THIS_PATH

    @property
    def declarations(self):
        return "static MAX7219 {name} = MAX7219({cs_pin}, {data_pin}, {dclk_pin});".format(
            name=self.cname(), cs_pin=self.cs_pin.value, data_pin=self.data_pin.value, dclk_pin=self.dclk_pin.value,
        )

class MAX7219Plugin(IPlugin, GenericDevicePlugin):

    REQUIRED_SETTINGS = ["cs_pin", "data_pin", "dclk_pin"]

    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, device):
        cs_pin = device.settings.get("cs_pin")
        data_pin = device.settings.get("data_pin")
        dclk_pin = device.settings.get("dclk_pin")
       
        return MAX7219(device.name, cs_pin, data_pin, dclk_pin)

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)