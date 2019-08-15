import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from raat.types import DeviceSource, DeviceInclude, LibraryInclude

from raat.devices.generic_device import GenericDevice, GenericDevicePlugin

from raat.types import Setting

THIS_PATH = Path(__file__).parent

class RAATServo(GenericDevice, namedtuple("RAATServo", ["name", "pin", "start_angle"])):

    __slots__ = ()

    sources = (DeviceSource(THIS_PATH, "servo.cpp"), )

    includes = (
        DeviceInclude(THIS_PATH, "servo.hpp"),
        LibraryInclude("Servo.h")
    )

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
        return "static RAATServo {name} = RAATServo({pin}, {start_angle});".format(
            name=self.cname(), pin=self.pin.value, start_angle=self.start_angle.value)


class ServoPlugin(IPlugin, GenericDevicePlugin):

    REQUIRED_SETTINGS = ["pin"]

    device_class = RAATServo

    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, device):

        self.verify_settings(device)

        start_angle = device.settings.get(
            "start_angle", Setting("start_angle", "", "0"))

        return RAATServo(device.name, device.settings["pin"], start_angle)

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
