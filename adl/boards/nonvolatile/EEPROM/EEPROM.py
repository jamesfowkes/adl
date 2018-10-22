from pathlib import Path

from adl.types import LocalSource, LibraryInclude

THIS_PATH = Path(__file__).parent

class EEPROM:

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

    def get_sources(self, target_type):
        return [s for s in self.sources if isinstance(s, target_type)]

    def get_includes(self, target_type):
        return [s for s in self.includes if isinstance(s, target_type)]