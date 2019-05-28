from pathlib import Path

from raat.types import LocalSource
from raat.types import SourceFileProvider

THIS_PATH = Path(__file__).parent


class Serial0(SourceFileProvider):

    sources = (
        LocalSource(THIS_PATH, "serial0.cpp"),
    )

    includes = ()

    def __init__(self, baudrate):
        self.baudrate = baudrate


class Serial0DueMicro(Serial0):

    sources = (
        LocalSource(THIS_PATH, "serial0-duemicro.cpp"),
    )

    includes = ()

    def __init__(self, baudrate):
        self.baudrate = baudrate
