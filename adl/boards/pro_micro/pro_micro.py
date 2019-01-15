import os
import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl import template_engine
from adl.boards.serial.serial0 import Serial0DueMicro
from adl.boards.nonvolatile.EEPROM.EEPROM import EEPROM
from adl.boards.generic_board import GenericBoard
from adl.types import LibraryInclude
from adl.boards.uno_etc import uno

THIS_PATH = Path(__file__).parent

class ProMicroBaseType(GenericBoard, namedtuple("ProMicroBaseType", 
    ["name", "serial", "nonvolatile", "devices", "parameters", "modules",
    "custom_code", "settings", "info", "log_modules", "defines", "arduino_libs",
    "fqbn"])):

    __slots__ = ()

    @property
    def template(self):
        return uno.template

    @property
    def log_printer(self):
        return "Serial";

    @property
    def progmem(self):
        return "PROGMEM";

    @property
    def required_core(self):
        return "arduino:avr"
