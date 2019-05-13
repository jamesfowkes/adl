import os
import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from raat.types import DeviceSource, DeviceInclude

from raat.devices.generic_device import GenericDevice, GenericDevicePlugin
from raat.types import Setting

THIS_PATH = Path(__file__).parent

class MT8870(GenericDevice, namedtuple("MT8870", ["name", "code_pins", "trigger_pin"])):

    __slots__ = ()

    sources = (DeviceSource(THIS_PATH, "MT8870.cpp"), )

    includes = (DeviceInclude(THIS_PATH, "MT8870.hpp"), )

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
        return "static MT8870 {name} = MT8870({code_pins}, {trigger_pin});".format(
            name=self.cname(), code_pins=",".join(self.code_pins.value), trigger_pin=self.trigger_pin.value
        )

class MT8870Plugin(IPlugin, GenericDevicePlugin):

    device_class = MT8870

    REQUIRED_SETTINGS = ["code_pins", "trigger_pin"]

    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, device):
        
        self.verify_settings(device)

        code_pins = device.settings["code_pins"].value.split(",")
        if len(code_pins) != 4:
            raise Exception("MT8870 expects 4 values for code pins (e.g. \"2,3,4,5)\"")

        code_pins = Setting("code_pins", "", code_pins)
        return MT8870(device.name, code_pins, device.settings["trigger_pin"])

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
