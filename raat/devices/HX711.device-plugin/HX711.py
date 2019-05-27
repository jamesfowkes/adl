import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from raat.types import LibraryInclude, DeviceSource, DeviceInclude

from raat.devices.generic_device import GenericDevice, GenericDevicePlugin
from raat.types import Setting

THIS_PATH = Path(__file__).parent

class HX711(GenericDevice, namedtuple("HX711", ["name"])):

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
        return "static HX711 {name} = HX711();".format(name=self.cname())


class HX711Plugin(IPlugin, GenericDevicePlugin):

    REQUIRED_SETTINGS = []

    device_class = HX711

    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, device):
        self.verify_settings(device)

        return HX711(device.name)

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
