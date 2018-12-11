import logging
import os

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.types import DeviceSource, DeviceInclude

from adl.devices.generic_device import GenericDevice, GenericDevicePlugin
from adl.types import Setting

THIS_PATH = Path(__file__).parent

def get_pins_from_string(s):
    pins = [int(p.strip()) for p in s.split(",")]
    if len(pins) > 8:
        raise Exception("Too many pins declared ({} > 8)".format(len(pins)))

    pins += ["PIN_NOT_USED"] * (8 - len(pins))
    return ", ". join([str(p) for p in pins])

class BinaryOutput(GenericDevice, namedtuple("BinaryOutput", ["name", "pins"])):

    __slots__ = ()

    sources = (DeviceSource(THIS_PATH, "binary-output.cpp"), )

    includes = (DeviceInclude(THIS_PATH, "binary-output.h"), )

    @property
    def setup(self):
        return "{name}.setup();".format(name=self.cname())

    @property
    def command_handler(self):
        return "return {name}.command_handler(command, reply);".format(name=self.cname())

    @property
    def directory(self):
        return THIS_PATH
        
    @property
    def declarations(self):
        return "static BinaryOutput {name} = BinaryOutput({pins});".format(
            name=self.cname(), pins=self.pins.value)

class BinaryOutputPlugin(IPlugin, GenericDevicePlugin):

    REQUIRED_SETTINGS = ["pins"]

    device_class = BinaryOutput

    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, device):
        self.verify_settings(device)

        pins = get_pins_from_string(device.settings["pins"].value)
        return BinaryOutput(device.name, Setting("pins", "", pins))

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
