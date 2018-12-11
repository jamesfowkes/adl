import os
import logging

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl import template_engine
from adl.boards.serial.serial0 import Serial0DueMicro
from adl.boards.generic_board import GenericBoard
from adl.boards.nonvolatile.EEPROM.EEPROM import EEPROM

from adl.boards.pro_micro.pro_micro import ProMicroBaseType

class ProMicro16MHz(ProMicroBaseType):

    __slots__ = ()

    def __new__(cls, *args, **kwargs):
        if kwargs["fqbn"] is None:
            kwargs["fqbn"] = "SparkFun:avr:promicro:cpu=16MHzatmega32U4"
        self = super(ProMicroBaseType, cls).__new__(cls, *args, **kwargs)
        return self

class ProMicro16MHzPlugin(IPlugin):
    def activate(self):
        pass

    def deactivate(self):
        pass
        
    def get(self, board, devices, parameters, modules):
        baudrate = board.attrs.get("baudrate", 115200)
        serial = Serial0DueMicro(baudrate)
        nonvolatile = EEPROM()

        return ProMicro16MHz(
            board.name, serial, nonvolatile, devices, parameters, modules,
            board.custom_code, board.settings, board.info, board.log_modules,
            board.defines, board.arduino_libs, fqbn=board.attrs.get("fqbn", None)
        )

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
