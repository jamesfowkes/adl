import logging
from pathlib import Path

from yapsy.IPlugin import IPlugin

from raat.modules.generic_module import GenericModule

from raat.types import ModuleSource, ModuleInclude

THIS_PATH = Path(__file__).parent

class OneShotTimerModule(GenericModule):

    sources = (ModuleSource(THIS_PATH, "raat-oneshot-timer.cpp"), )
    includes = (ModuleInclude(THIS_PATH, "raat-oneshot-timer.h"), )

    @property
    def directory(self):
        return THIS_PATH

class OneShotTimerPlugin(IPlugin):
    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, param):
        return OneShotTimerModule()

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
