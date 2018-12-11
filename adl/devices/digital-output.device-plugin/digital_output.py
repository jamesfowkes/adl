import os
import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.types import DeviceSource, DeviceInclude

from adl.devices.generic_device import GenericDevice

THIS_PATH = Path(__file__).parent

class DigitalOutput(GenericDevice, namedtuple("DigitalOutput", ["name", "pin"])):

    __slots__ = ()

    sources = (DeviceSource(THIS_PATH, "digital-output.cpp"), )

    includes = (DeviceInclude(THIS_PATH, "digital-output.h"), )

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
        return "static DigitalOutput {name} = DigitalOutput({pin});".format(
            name=self.cname(), pin=self.pin.value)

class DigitalOutputPlugin(IPlugin):
    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, device):
        return DigitalOutput(device.name, device.settings["pin"])

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
