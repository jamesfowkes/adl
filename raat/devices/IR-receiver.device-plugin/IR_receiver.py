import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from raat.types import DeviceSource, DeviceInclude, LibraryInclude

from raat.devices.generic_device import GenericDevice, GenericDevicePlugin

THIS_PATH = Path(__file__).parent


class IR_Receiver(GenericDevice, namedtuple("IR_Receiver", ["name", "pin"])):

    __slots__ = ()

    sources = (DeviceSource(THIS_PATH, "IR-receiver.cpp"), )

    includes = (
        DeviceInclude(THIS_PATH, "IR-receiver.hpp"),
        LibraryInclude("IRremote.h")
    )

    @property
    def setup(self):
        return "{name}.setup();".format(name=self.cname())

    @property
    def directory(self):
        return THIS_PATH

    @property
    def required_libraries(self):
        return ["IRremote"]

    @property
    def declarations(self):
        return "static IR_Receiver {name} = IR_Receiver({pin});".format(
            name=self.cname(), pin=self.pin.value)


class IR_ReceiverPlugin(IPlugin, GenericDevicePlugin):

    REQUIRED_SETTINGS = ["pin"]

    device_class = IR_Receiver

    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, device):
        self.verify_settings(device)
        return IR_Receiver(device.name, device.settings["pin"])

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
