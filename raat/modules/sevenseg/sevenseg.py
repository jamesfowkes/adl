import logging
from pathlib import Path

from yapsy.IPlugin import IPlugin

from raat.modules.generic_module import GenericModule

from raat.types import ModuleSource, ModuleInclude

THIS_PATH = Path(__file__).parent


class SevenSeg(GenericModule):

    sources = (ModuleSource(THIS_PATH, "sevenseg.cpp"), )

    includes = (ModuleInclude(THIS_PATH, "sevenseg.hpp"), )

    @property
    def directory(self):
        return THIS_PATH


class SevenSegPlugin(IPlugin):
    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, param):
        return SevenSeg()

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
