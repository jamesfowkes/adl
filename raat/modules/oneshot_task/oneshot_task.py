import logging
from pathlib import Path

from yapsy.IPlugin import IPlugin

from raat.modules.generic_module import GenericModule
from raat.modules.oneshot_timer.oneshot_timer import OneShotTimerModule

from raat.types import ModuleSource, ModuleInclude

THIS_PATH = Path(__file__).parent

class OneShotTaskModule(GenericModule):
    
    sources = OneShotTimerModule().sources
    sources += (ModuleSource(THIS_PATH, "raat-oneshot-task.cpp"),)

    includes = OneShotTimerModule().includes
    includes += (ModuleInclude(THIS_PATH, "raat-oneshot-task.hpp"),)

    @property
    def directory(self):
        return THIS_PATH

class OneShotTaskPlugin(IPlugin):
    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, param):
        return OneShotTaskModule()

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
