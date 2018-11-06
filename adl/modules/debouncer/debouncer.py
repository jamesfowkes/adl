import logging
from pathlib import Path

from yapsy.IPlugin import IPlugin

from adl.modules.generic_module import GenericModule

from adl.types import ModuleSource, ModuleInclude

THIS_PATH = Path(__file__).parent

class DebouncerModule(GenericModule):
    
    @property
    def directory(self):
        return THIS_PATH

    @property
    def sources(self):
        return [ModuleSource(THIS_PATH, "adl-debouncer.cpp")]

    @property
    def includes(self):
        return [ModuleInclude(THIS_PATH, "adl-debouncer.h")]

class DebouncerPlugin(IPlugin):
    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, param):
        return DebouncerModule()

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
