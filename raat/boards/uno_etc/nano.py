from raat.boards.serial.serial0 import Serial0
from raat.boards.nonvolatile.EEPROM.EEPROM import EEPROM

from raat.boards.uno_etc.uno import UnoBaseType, UnoPlugin


class Nano168(UnoBaseType):

    __slots__ = ()

    def __new__(cls, *args, **kwargs):
        if kwargs[ "fqbn"] is None:
            kwargs["fqbn"] = "arduino:avr:nano:cpu=atmega168"
        self = super(UnoBaseType, cls).__new__(cls, *args, **kwargs)
        return self


class Nano(UnoBaseType):

    __slots__ = ()

    def __new__(cls, *args, **kwargs):
        if kwargs["fqbn"] is None:
            kwargs["fqbn"] = "arduino:avr:nano:cpu=atmega328"
        self = super(UnoBaseType, cls).__new__(cls, *args, **kwargs)
        return self


class NanoPlugin(UnoPlugin):

    def get(self, board, devices, parameters, modules):
        baudrate = board.attrs.get("baudrate", 115200)
        serial = Serial0(baudrate)
        nonvolatile = EEPROM()

        return Nano(
            board.name, serial, nonvolatile, devices, parameters, modules,
            board.custom_code, board.settings, board.info, board.log_modules,
            board.defines, board.arduino_libs, fqbn=board.attrs.get("fqbn", None)
        )
