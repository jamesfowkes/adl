import logging
from pathlib import Path

from yapsy.IPlugin import IPlugin

from adl.modules.generic_module import GenericModule
from adl.modules.oneshot_timer.oneshot_timer import OneShotTimerModule

from adl.types import ModuleSource, ModuleInclude

THIS_PATH = Path(__file__).parent

class OneShotTaskModule(GenericModule):
	
	@property
	def directory(self):
		return THIS_PATH

	@property
	def sources(self):
		sources = OneShotTimerModule().sources
		sources.append(ModuleSource(THIS_PATH, "adl-oneshot-task.cpp"))
		return sources

	@property
	def includes(self):
		includes = OneShotTimerModule().includes
		includes.append(ModuleInclude(THIS_PATH, "adl-oneshot-task.h"))
		return includes

class OneShotTaskPlugin(IPlugin):
	def activate(self):
		pass

	def deactivate(self):
		pass

	def get(self, param):
		return OneShotTaskModule()

	def set_log_level(self, level):
		logging.getLogger(__name__).setLevel(level)
