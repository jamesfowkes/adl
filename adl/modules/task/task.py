import logging
from pathlib import Path

from yapsy.IPlugin import IPlugin

from adl.modules.generic_module import GenericModule
from adl.modules.oneshot_task.oneshot_task import OneShotTaskModule

from adl.types import ModuleSource, ModuleInclude

THIS_PATH = Path(__file__).parent

class TaskModule(GenericModule):
    
    @property
    def directory(self):
        return THIS_PATH

    @property
    def sources(self):
        sources = OneShotTaskModule().sources
        sources.append(ModuleSource(THIS_PATH, "adl-task.cpp"))
        return sources

    @property
    def includes(self):
        includes = OneShotTaskModule().includes
        includes.append(ModuleInclude(THIS_PATH, "adl-task.h"))
        return includes

class TaskPlugin(IPlugin):
    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, param):
        return TaskModule()

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
