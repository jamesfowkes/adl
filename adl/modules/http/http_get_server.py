import logging
from pathlib import Path

from yapsy.IPlugin import IPlugin

from adl.modules.generic_module import GenericModule

from adl.types import ModuleSource, ModuleInclude, ADLSource, ADLInclude

THIS_PATH = Path(__file__).parent

class HTTPGetServerModule(GenericModule):
    
    sources = (
        ADLSource("utility", "adl-buffer.cpp"),
        ModuleSource(THIS_PATH, "http-get-server.cpp")
    )

    includes = (
        ADLSource("utility", "adl-buffer.h"),
        ModuleInclude(THIS_PATH, "http-get-server.h")
    )

    @property
    def directory(self):
        return THIS_PATH

class DebouncerPlugin(IPlugin):
    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, param):
        return HTTPGetServerModule()

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
