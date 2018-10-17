import logging
import os

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.types import DeviceSource, DeviceInclude

from adl.devices.generic_device import GenericDevice

from adl.types import Setting

THIS_PATH = Path(__file__).parent

class RandomPWM(GenericDevice, namedtuple("RandomPWM", ["name", "pin", "interval", "low_limit", "high_limit"])):

    __slots__ = ()

    @property
    def setup(self):
        return "{name}.setup();".format(name=self.cname())

    @property
    def directory(self):
        return THIS_PATH

    @property
    def sources(self):
        return [DeviceSource(THIS_PATH, "random-pwm.cpp")]

    @property
    def includes(self):
        return [DeviceInclude(THIS_PATH, "random-pwm.h")]

    @property
    def declarations(self):
        return "static RandomPWM {name} = RandomPWM({pin}, {interval}, {low_limit}, {high_limit});".format(
            name=self.cname(), pin=self.pin.value, interval=self.interval.value, low_limit=self.low_limit.value, high_limit=self.high_limit.value)

class RandomPWMPlugin(IPlugin):
    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, device):
        return RandomPWM(
            device.name, device.settings["pin"], device.settings["interval"],
            device.settings.get("lowlimit", Setting("lowlimit", "", "0")),
            device.settings.get("highlimit", Setting("highlimit", "", "255"))
        )

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
