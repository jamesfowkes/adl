import os
import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.types import LibraryInclude, DeviceSource, DeviceInclude

from adl.devices.generic_device import GenericDevice, GenericDevicePlugin

from adl.devices import device_utils

THIS_PATH = Path(__file__).parent

class Thermistor(GenericDevice, namedtuple("Thermistor", ["name", "pin", "R25", "beta", "divider_type", "other_resistance"])):

    __slots__ = ()

    sources = device_utils.get_device_class("Potential Divider").sources
    sources += (DeviceSource(THIS_PATH, "thermistor.cpp"), )

    includes = device_utils.get_device_class("Potential Divider").includes
    includes += (DeviceInclude(THIS_PATH, "thermistor.h"), )

    @property
    def setup(self):
        return "{name}.setup();".format(name=self.cname())

    @property
    def directory(self):
        return THIS_PATH

    @property
    def declarations(self):
        return "static Thermistor {name} = Thermistor({pin}, {R25}, {beta}, {other_r}, {divider_type});".format(
            name=self.cname(), pin=self.pin.value, R25=self.R25.value, beta=self.beta.value, other_r=self.other_resistance.value, divider_type=self.divider_type.value)

class ThermistorPlugin(IPlugin, GenericDevicePlugin):

    REQUIRED_SETTINGS = ["pin", "divider_type", "other_resistance", "R25", "beta"]

    device_class = Thermistor

    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, device):
        self.verify_settings(device)
        return Thermistor(device.name, device.settings["pin"], device.settings["R25"], device.settings["beta"], device.settings["divider_type"], device.settings["other_resistance"])

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
