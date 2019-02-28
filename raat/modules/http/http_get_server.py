import logging
from pathlib import Path

from yapsy.IPlugin import IPlugin

from raat.modules.generic_module import GenericModule

from raat.types import ModuleSource, ModuleInclude, RAATSource, RAATInclude

THIS_PATH = Path(__file__).parent

class HTTPGetServerModule(GenericModule):
    
    sources = (
        RAATSource("utility", "raat-buffer.cpp"),
        ModuleSource(THIS_PATH, "http-get-server.cpp")
    )

    includes = (
        RAATSource("utility", "raat-buffer.hpp"),
        ModuleInclude(THIS_PATH, "http-get-server.hpp")
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
