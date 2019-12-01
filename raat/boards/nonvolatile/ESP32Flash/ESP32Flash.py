from pathlib import Path

from raat.types import LocalSource, LibraryInclude
from raat.types import SourceFileProvider

THIS_PATH = Path(__file__).parent


class ESP32Flash(SourceFileProvider):

    sources = (LocalSource(THIS_PATH, "raat-nv-esp32flash.cpp"), )
    includes = (LibraryInclude("EEPROM.h"), )

    def __init__(self):
        pass

    @property
    def declarations(self):
        return ""

    @property
    def setup(self):
        return "EEPROM.begin(512);"

    @property
    def address_type(self):
        return "uint16_t"
