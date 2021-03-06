import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from raat.types import DeviceSource, DeviceInclude

from raat.devices.generic_device import GenericDevice

THIS_PATH = Path(__file__).parent


class DigitalInput(GenericDevice, namedtuple("DigitalInput", ["name", "pin"])):

    __slots__ = ()

    sources = (DeviceSource(THIS_PATH, "digital-input.cpp"), )

    includes = (DeviceInclude(THIS_PATH, "digital-input.hpp"), )

    @property
    def setup(self):
        return "{name}.setup();".format(name=self.cname())

    @property
    def directory(self):
        return THIS_PATH

    @property
    def declarations(self):
        return "static DigitalInput {name} = DigitalInput({pin});".format(
            name=self.cname(), pin=self.pin.value)


class DigitalInputPlugin(IPlugin):

    device_class = DigitalInput

    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, device):
        return DigitalInput(device.name, device.settings["pin"])

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
