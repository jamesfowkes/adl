import os
import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.types import Setting, DeviceSource, DeviceInclude, LibraryInclude

from adl.devices.generic_device import GenericDevice, GenericDevicePlugin

THIS_PATH = Path(__file__).parent

class ENC28J60(GenericDevice, namedtuple("ENC28J60", ["name"])):

    __slots__ = ()

    sources = (DeviceSource(THIS_PATH, "ENC28J60ADL.cpp"), )

    includes = (
        LibraryInclude("EtherCard.h"),
        DeviceInclude(THIS_PATH, "ENC28J60ADL.h")
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
        return "static ENC28J60ADL {name} = ENC28J60ADL();".format(name=self.cname())

class ENC28J60Plugin(IPlugin, GenericDevicePlugin):

    device_class = ENC28J60

    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, device):
        return ENC28J60(device.name)

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
