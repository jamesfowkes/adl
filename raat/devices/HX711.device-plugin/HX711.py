import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from raat.types import LibraryInclude, DeviceSource, DeviceInclude

from raat.devices.generic_device import GenericDevice, GenericDevicePlugin

THIS_PATH = Path(__file__).parent


class HX711RAAT(GenericDevice, namedtuple("HX711", ["name", "dout_pin", "sck_pin"])):

    __slots__ = ()

    sources = (DeviceSource(THIS_PATH, "hx711-raat.cpp"), )

    includes = (
        DeviceInclude(THIS_PATH, "hx711-raat.hpp"),
        LibraryInclude("HX711.h")
    )

    @property
    def setup(self):
        return "{name}.setup();".format(name=self.cname())

    @property
    def directory(self):
        return THIS_PATH

    @property
    def required_libraries(self):
        return ["HX711 Arduino Library"]

    @property
    def declarations(self):
        return "static HX711RAAT {name} = HX711RAAT({dout_pin}, {sck_pin});".format(
            name=self.cname(), dout_pin=self.dout_pin, sck_pin=self.sck_pin)


class HX711Plugin(IPlugin, GenericDevicePlugin):

    REQUIRED_SETTINGS = ["dout_pin", "sck_pin"]

    device_class = HX711RAAT

    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, device):
        self.verify_settings(device)
        return HX711RAAT(device.name, device.settings["dout_pin"].value, device.settings["sck_pin"].value)

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
