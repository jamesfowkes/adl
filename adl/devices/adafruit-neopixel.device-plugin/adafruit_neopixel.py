import logging
import os

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.types import LibraryInclude, DeviceSource, DeviceInclude

from adl.devices.generic_device import GenericDevice, GenericDevicePlugin
from adl.types import Setting

THIS_PATH = Path(__file__).parent

class Adafruit_Neopixel(GenericDevice, namedtuple("Adafruit_Neopixel", ["name", "pin", "npixels"])):

    __slots__ = ()

    @property
    def setup(self):
        return "{name}.setup();".format(name=self.cname())

    @property
    def directory(self):
        return THIS_PATH

    @property
    def sources(self):
        return [DeviceSource(THIS_PATH, "adafruit-neopixel-adl.cpp")]

    @property
    def includes(self):
        return [
            DeviceInclude(THIS_PATH, "adafruit-neopixel-adl.h"),
            LibraryInclude("Adafruit_NeoPixel.h")
        ]

    @property
    def declarations(self):
        return "static AdafruitNeoPixelADL {name} = AdafruitNeoPixelADL({pin}, {npixels});".format(
            name=self.cname(), pin=self.pin.value, npixels=self.npixels.value)

class Adafruit_NeopixelPlugin(IPlugin, GenericDevicePlugin):

    REQUIRED_SETTINGS = ["pin", "npixels"]

    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, device):
        self.verify_settings(device)
        return Adafruit_Neopixel(device.name, device.settings["pin"], device.settings["npixels"])

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
