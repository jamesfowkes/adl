import logging
import os

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from raat.types import DeviceSource, DeviceInclude, LibraryInclude

from raat.devices.generic_device import GenericDevice, GenericDevicePlugin
from raat.types import Setting

THIS_PATH = Path(__file__).parent

class MAX7219(GenericDevice, namedtuple("MAX7219", ["name", "cs_pin", "data_pin", "dclk_pin", "device_count"])):

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
        return "static MAX7219 {name} = MAX7219({cs_pin}, {data_pin}, {dclk_pin}, {device_count});".format(
            name=self.cname(), cs_pin=self.cs_pin.value, data_pin=self.data_pin.value,
            dclk_pin=self.dclk_pin.value, device_count=self.device_count.value
        )

class MAX7219Plugin(IPlugin, GenericDevicePlugin):

    REQUIRED_SETTINGS = ["cs_pin", "data_pin", "dclk_pin", "device_count"]

    device_class = MAX7219

    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, device):

        self.verify_settings(device)

        cs_pin = device.settings.get("cs_pin")
        data_pin = device.settings.get("data_pin")
        dclk_pin = device.settings.get("dclk_pin")
        device_count = device.settings.get("device_count")
       
        return MAX7219(device.name, cs_pin, data_pin, dclk_pin, device_count)

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
