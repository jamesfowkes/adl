import os
import logging

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl import template_engine
from adl.boards.serial.serial0 import Serial0
from adl.boards.generic_board import GenericBoard

class UnoBaseType(GenericBoard, namedtuple("UnoBaseType", 
    ["name", "serial", "devices", "parameters", "modules", "custom_code", "settings", "info", "log_modules"])):

    __slots__ = ()

    def code(self, adl):
        return template_engine.render_board("uno.template", adl=adl, board=self)

    @property
    def log_printer(self):
        return "Serial";

    @property
    def progmem(self):
        return "PROGMEM";

class Uno(UnoBaseType):
    
    __slots__ = ()

    def __new__(cls, *args, **kwargs):
        self = super(UnoBaseType, cls).__new__(cls, *args, **kwargs)
        return self

    @property
    def fqbn(self):
        return "arduino:avr:uno"

class UnoPlugin(IPlugin):
    def activate(self):
        pass

    def deactivate(self):
        pass
        
    def get(self, board, devices, parameters, modules):
        baudrate = board.attrs.get("baudrate", 115200)
        serial = Serial0(baudrate)
        return Uno(board.name, serial, devices, parameters, modules, board.custom_code, board.settings, board.info, board.log_modules)

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
