import logging
import os
from pathlib import Path
from collections import namedtuple

from yapsy.IPlugin import IPlugin

from raat.types import LibraryInclude, DeviceInclude, DeviceSource
from raat.devices.generic_device import GenericDevice

THIS_PATH = Path(__file__).parent

class RFID_RC522(GenericDevice, namedtuple("RFID_RC522", ["name", "ss", "rst"])):

    __slots__ = ()

    sources = (DeviceSource(THIS_PATH, "rfid-rc522.cpp"), )

    includes = (
        LibraryInclude("MFRC522.h"),
        DeviceInclude(THIS_PATH, "rfid-rc522.hpp")
    )

    @property
    def setup(self):
        return "{name}.setup();".format(name=self.cname())

    @property
    def directory(self):
        return THIS_PATH

    @property
    def declarations(self):
        return "static RFID_RC522 {name} = RFID_RC522({ss}, {rst});".format(
            name=self.cname(), ss=self.ss.value, rst=self.rst.value)

    @property
    def required_libraries(self):
        return ["MFRC522"]

class RFID_RC522Plugin(IPlugin):

    device_class = RFID_RC522

    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, device):
        return RFID_RC522(device.name, device.settings["ss"], device.settings["rst"])

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
