import os
import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from raat.types import Setting, DeviceSource, DeviceInclude, LibraryInclude

from raat.devices.generic_device import GenericDevice, GenericDevicePlugin

THIS_PATH = Path(__file__).parent

class ENC28J60RAAT(GenericDevice, namedtuple("ENC28J60RAAT", ["name", "cs_pin"])):

    __slots__ = ()

    sources = (DeviceSource(THIS_PATH, "ENC28J60RAAT.cpp"), )

    includes = (
        LibraryInclude("EtherCard.h"),
        DeviceInclude(THIS_PATH, "ENC28J60RAAT.hpp")
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
        return "static ENC28J60RAAT {name} = ENC28J60RAAT({cs_pin});".format(name=self.cname(), cs_pin=self.cs_pin)

class ENC28J60Plugin(IPlugin, GenericDevicePlugin):

    REQUIRED_SETTINGS = ["cs_pin"]

    device_class = ENC28J60RAAT

    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, device):
        self.verify_settings(device)

        return ENC28J60RAAT(device.name, device.settings["cs_pin"].value)

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
