import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from raat.types import DeviceSource, DeviceInclude

from raat.devices.generic_device import GenericDevice

THIS_PATH = Path(__file__).parent


class MCP41XXX(GenericDevice, namedtuple("MCP41XXX", ["name", "cs_pin"])):

    __slots__ = ()

    sources = (DeviceSource(THIS_PATH, "MCP41XXX.cpp"), )

    includes = (DeviceInclude(THIS_PATH, "MCP41XXX.hpp"),)

    @property
    def setup(self):
        return "{name}.setup();".format(name=self.cname())

    @property
    def directory(self):
        return THIS_PATH

    @property
    def declarations(self):
        return "static MCP41XXX {name} = MCP41XXX({cs_pin});".format(name=self.cname(), cs_pin=self.cs_pin.value)


class MCP41XXXPlugin(IPlugin):

    device_class = MCP41XXX

    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, device):
        return MCP41XXX(device.name, device.settings["cs_pin"])

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
