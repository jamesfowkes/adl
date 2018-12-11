import logging
from pathlib import Path

from yapsy.IPlugin import IPlugin

from adl.modules.generic_module import GenericModule

from adl.types import ModuleSource, ModuleInclude

THIS_PATH = Path(__file__).parent

class GridIndexerModule(GenericModule):
    
    sources = (ModuleSource(THIS_PATH, "grid-indexer.cpp"), )

    includes = (ModuleInclude(THIS_PATH, "grid-indexer.h"), )

    @property
    def directory(self):
        return THIS_PATH

class GridIndexerPlugin(IPlugin):
    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, param):
        return GridIndexerModule()

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
