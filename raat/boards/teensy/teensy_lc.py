import logging

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from raat.boards.serial.serial0 import Serial0DueMicro
from raat.boards.generic_board import GenericBoard
from raat.boards.nonvolatile.EEPROM.EEPROM import EEPROM

from raat.boards.uno_etc import uno


class TeensyLC(
    GenericBoard,
    namedtuple(
        "TeensyLC",
        [
            "name", "serial", "nonvolatile", "devices", "parameters", "modules",
            "custom_code", "settings", "info", "log_modules", "defines", "arduino_libs",
            "fqbn"
        ]
    )
):

    __slots__ = ()

    @property
    def template(self):
        return uno.TEMPLATE

    @property
    def log_printer(self):
        return "Serial"

    @property
    def progmem(self):
        return "PROGMEM"

    @property
    def required_core(self):
        return "teensy:avr:teensy3"


class TeensyLCPlugin(IPlugin):
    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, board, devices, parameters, modules):
        baudrate = board.attrs.get("baudrate", 115200)
        serial = Serial0DueMicro(baudrate)
        nonvolatile = EEPROM()

        return TeensyLC(
            board.name, serial, nonvolatile, devices, parameters, modules,
            board.custom_code, board.settings, board.info, board.log_modules,
            board.defines, board.arduino_libs, fqbn=board.attrs.get("fqbn", "teensy:avr:teensyLC")
        )

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
