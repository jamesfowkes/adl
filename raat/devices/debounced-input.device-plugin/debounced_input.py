import logging
import os

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from raat.types import RAATSource, RAATInclude
from raat.types import DeviceSource, DeviceInclude
from raat.types import LibraryInclude, Setting
from raat.devices.generic_device import GenericDevice

from raat.modules.debouncer.debouncer import DebouncerModule

THIS_PATH = Path(__file__).parent

class DebouncedInput(GenericDevice, namedtuple("DebouncedInput", ["name", "pin", "debounce_time", "pullup", "invert"])):

    __slots__ = ()

    sources = DebouncerModule().sources
    sources += (DeviceSource(THIS_PATH, "debounced-input.cpp"),)
        
    includes = DebouncerModule().includes
    includes += (DeviceInclude(THIS_PATH, "debounced-input.hpp"), )

    @property
    def setup(self):
        return "{name}.setup();".format(name=self.cname())

    @property
    def directory(self):
        return THIS_PATH

    @property
    def declarations(self):
        return "static DebouncedInput {name} = DebouncedInput({pin}, {debounce_time}, {pullup}, {invert});".format(
            name=self.cname(), pin=self.pin.value, debounce_time=self.debounce_time.value,
            pullup=self.pullup.value, invert=self.invert.value
        )

class DebouncedInputPlugin(IPlugin):

    REQUIRED_SETTINGS = ["pin"]

    device_class = DebouncedInput

    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, device):

        debounce_time = device.settings.get("debounce_time", Setting("debounce_time","","50"))
        pullup = device.settings.get("pullup", Setting("pullup","","true"))
        invert = device.settings.get("invert", Setting("invert","","false"))

        return DebouncedInput(device.name, 
            device.settings["pin"], debounce_time, pullup, invert)

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
