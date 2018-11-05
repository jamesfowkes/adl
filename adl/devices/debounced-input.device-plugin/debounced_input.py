import logging
import os

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.types import ADLSource, ADLInclude
from adl.types import DeviceSource, DeviceInclude
from adl.types import LibraryInclude, Setting
from adl.devices.generic_device import GenericDevice

THIS_PATH = Path(__file__).parent

class DebouncedInput(GenericDevice, namedtuple("DebouncedInput", ["name", "pin", "debounce_time", "pullup"])):

    __slots__ = ()

    @property
    def setup(self):
        return "{name}.setup();".format(name=self.cname())

    @property
    def directory(self):
        return THIS_PATH

    @property
    def sources(self):
        return [
            ADLSource("utility", "adl-util-debouncer.cpp"),
            DeviceSource(THIS_PATH, "debounced-input.cpp")
        ]

    @property
    def includes(self):
        return [
            ADLInclude("utility", "adl-util-debouncer.h"),
            DeviceInclude(THIS_PATH, "debounced-input.h")
        ]

    @property
    def declarations(self):
        return "static DebouncedInput {name} = DebouncedInput({pin}, {debounce_time}, {pullup});".format(
            name=self.cname(), pin=self.pin.value, debounce_time=self.debounce_time.value, pullup=self.pullup.value)

class TimedOnOffPlugin(IPlugin):

    REQUIRED_SETTINGS = ["pin"]

    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, device):

        debounce_time = device.settings.get("debounce_time", Setting("debounce_time","","50"))
        pullup = device.settings.get("pullup", Setting("pullup","","true"))

        return DebouncedInput(device.name, 
            device.settings["pin"], debounce_time, pullup)

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
