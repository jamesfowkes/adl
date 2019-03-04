import logging
from pathlib import Path

from yapsy.IPlugin import IPlugin

from raat.modules.generic_module import GenericModule
from raat.modules.oneshot_task.oneshot_task import OneShotTaskModule

from raat.types import ModuleSource, ModuleInclude

THIS_PATH = Path(__file__).parent

class TaskModule(GenericModule):
    
    sources = OneShotTaskModule().sources
    sources += (ModuleSource(THIS_PATH, "raat-task.cpp"),)
    
    includes = OneShotTaskModule().includes
    includes += (ModuleInclude(THIS_PATH, "raat-task.hpp"),)
    
    @property
    def directory(self):
        return THIS_PATH

class TaskPlugin(IPlugin):
    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, param):
        return TaskModule()

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
