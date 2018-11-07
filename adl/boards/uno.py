import os
import logging

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl import template_engine
from adl.boards.serial.serial0 import Serial0
from adl.boards.nonvolatile.EEPROM.EEPROM import EEPROM
from adl.boards.generic_board import GenericBoard
from adl.types import LibraryInclude

THIS_PATH = Path(__file__).parent

class UnoBaseType(GenericBoard, namedtuple("UnoBaseType", 
    ["name", "serial", "nonvolatile", "devices", "parameters", "modules",
    "custom_code", "settings", "info", "log_modules", "defines", "fqbn"])):

    __slots__ = ()

    @property
    def template(self):
        #return THIS_PATH.joinpath("uno.template")
        return "uno.template"
    @property
    def log_printer(self):
        return "Serial";

    @property
    def progmem(self):
        return "PROGMEM";

    @property
    def required_core(self):
        return "arduino:avr"

class Uno(UnoBaseType):
    
    __slots__ = ()

    def __new__(cls, *args, **kwargs):
        if kwargs["fqbn"] is None:
            kwargs["fqbn"] = "arduino:avr:uno"
        self = super(UnoBaseType, cls).__new__(cls, *args, **kwargs)
        return self

class UnoPlugin(IPlugin):
    def activate(self):
        pass

    def deactivate(self):
        pass
        
    def get(self, board, devices, parameters, modules):
        baudrate = board.attrs.get("baudrate", 115200)
        serial = Serial0(baudrate)
        nonvolatile = EEPROM()

        return Uno(
            board.name, serial, nonvolatile, devices, parameters, modules,
            board.custom_code, board.settings, board.info, board.log_modules,
            board.defines, fqbn=board.attrs.get("fqbn", None)
        )

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
