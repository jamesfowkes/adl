from pathlib import Path

from adl.types import LocalSource, LibraryInclude
from adl.types import SourceFileProvider

THIS_PATH = Path(__file__).parent

class EEPROM(SourceFileProvider):

    def __init__(self):
        pass

    @property
    def declarations(self):
        return ""

    @property
    def setup(self):
        return ""

    @property
    def address_type(self):
        return "uint16_t"

    @property
    def sources(self):
        return [
            LocalSource(THIS_PATH, "adl-nv-eeprom.cpp")
        ]

    @property
    def includes(self):
        return [
            LibraryInclude("EEPROM.h")
        ]
