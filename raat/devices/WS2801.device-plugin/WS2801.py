import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from raat.types import LibraryInclude, DeviceSource, DeviceInclude

from raat.parameters.rgb.rgb import RGBParam
from raat.devices.generic_device import GenericDevice, GenericDevicePlugin
from raat.types import Setting

THIS_PATH = Path(__file__).parent


class WS2801(GenericDevice, namedtuple("WS2801", ["name", "data_pin", "clock_pin", "npixels"])):

    __slots__ = ()

    sources = (DeviceSource(THIS_PATH, "WS2801.cpp"), )
    sources += RGBParam.sources

    includes = (
        DeviceInclude(THIS_PATH, "WS2801.hpp"),
        LibraryInclude("Adafruit_WS2801.h")
    )
    includes += RGBParam.includes

    @property
    def setup(self):
        return "{name}.setup();".format(name=self.cname())

    @property
    def directory(self):
        return THIS_PATH

    @property
    def required_libraries(self):
        return ["Adafruit WS2801 Library"]

    @property
    def declarations(self):
        return "static WS2801 {name} = WS2801({data_pin}, {clock_pin}, {npixels});".format(
            name=self.cname(), data_pin=self.data_pin.value, clock_pin=self.clock_pin.value, 
            npixels=self.npixels.value)


class WS2801Plugin(IPlugin, GenericDevicePlugin):

    REQUIRED_SETTINGS = ["data_pin", "clock_pin", "npixels"]

    device_class = WS2801

    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, device):
        self.verify_settings(device)

        return WS2801(device.name,
            device.settings["data_pin"],
            device.settings["clock_pin"],
            device.settings["npixels"],
        )

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
