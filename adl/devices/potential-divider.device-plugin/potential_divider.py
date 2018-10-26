import os
import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.types import LibraryInclude, DeviceSource, DeviceInclude

from adl.devices.generic_device import GenericDevice, GenericDevicePlugin

THIS_PATH = Path(__file__).parent

class PotentialDivider(GenericDevice, namedtuple("PotentialDivider", ["name", "pin", "divider_type", "other_resistance"])):

    __slots__ = ()

    @property
    def setup(self):
        return "{name}.setup();".format(name=self.cname())

    @property
    def directory(self):
        return THIS_PATH

    @property
    def sources(self):
        return [DeviceSource(THIS_PATH, "potential-divider.cpp")]

    @property
    def includes(self):
        return [DeviceInclude(THIS_PATH, "potential-divider.h")]

    @property
    def declarations(self):
        return "static PotentialDivider {name} = PotentialDivider({pin}, {other_r}, {divider_type});".format(
            name=self.cname(), pin=self.pin.value, other_r=self.other_resistance.value, divider_type=self.divider_type.value)

class PotentialDividerPlugin(IPlugin, GenericDevicePlugin):

    REQUIRED_SETTINGS = ["pin", "divider_type", "other_resistance"]

    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, device):
        self.verify_settings(device)
        return PotentialDivider(device.name, device.settings["pin"], device.settings["divider_type"], device.settings["other_resistance"])

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
