import os
import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from raat.types import DeviceSource, DeviceInclude

from raat.devices.generic_device import GenericDevice, GenericDevicePlugin

from raat.types import Setting

THIS_PATH = Path(__file__).parent

class DigitalOutput(GenericDevice, namedtuple("DigitalOutput", ["name", "pin", "startup_state"])):

    __slots__ = ()

    sources = (DeviceSource(THIS_PATH, "digital-output.cpp"), )

    includes = (DeviceInclude(THIS_PATH, "digital-output.hpp"), )

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
        return "static DigitalOutput {name} = DigitalOutput({pin}, STARTUP_STATE_{startup_state});".format(
            name=self.cname(), pin=self.pin.value, startup_state=self.startup_state.value)

class DigitalOutputPlugin(IPlugin, GenericDevicePlugin):

    REQUIRED_SETTINGS = ["pin"]

    device_class = DigitalOutput

    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, device):

        self.verify_settings(device)

        startup_state = device.settings.get("startup_state", Setting("startup_state", "", "LOW"))

        return DigitalOutput(device.name, device.settings["pin"], startup_state)

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
