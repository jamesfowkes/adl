import os
import logging
from collections import namedtuple

from pathlib import Path

from adl.types import LocalInclude, LibraryInclude

def get_module_logger():
	return logging.getLogger(__name__)

class SketchPath(namedtuple("SketchPath", ["folder", "extension"])):

	__slots__ = ()

	@property
	def full_name(self):
		return self.folder + self.extension

	@property
	def full_path(self):
		return Path.joinpath(self.folder, self.folder + self.extension)

class GenericBoard:

	def sketch_path(self, extension=".ino"):
		sketch_name = self.name
		if sketch_name[0].isdigit():
			get_module_logger().warning("Name starts with numeric value. Prefixing with underscore.")
			sketch_name = "_" + sketch_name

		if " " in sketch_name:
			get_module_logger().warning("Name contains spaces. Replacing with underscores.")
			sketch_name = sketch_name.replace(" ", "_")

		full_sketch_name = sketch_name + extension

		return Path(sketch_name).joinpath(full_sketch_name)

	def adl_sources(self, full_path):
		all_deps = []
		for d in self.devices:
			for dep in d.adl_dependencies:
				for src in dep.sources:
					inc_path = Path.joinpath(dep.directory, src) if full_path else src
					all_deps.append(inc_path)

		return set(all_deps)

	def adl_includes(self, full_path):
		all_deps = []
		for d in self.devices:
			for dep in d.adl_dependencies:
				for header in dep.headers:
					inc_path = Path.joinpath(dep.directory, header) if full_path else header
					all_deps.append(inc_path)

		return set(all_deps)

	def device_includes(self, full_path):
		all_includes = []
		for d in self.devices:
			for include in d.includes:
				if type(include) is LocalInclude:
					inc_path = Path.joinpath(d.directory, include.filename) if full_path else include.filename
					all_includes.append(inc_path)

		for p in self.parameters:
			for include in p.includes:
				inc_path = Path.joinpath(p.directory, include) if full_path else include
				all_includes.append(inc_path)

		all_includes = set(all_includes)
		return set(all_includes)

	def library_includes(self, full_path):
		all_includes = []
		for d in self.devices:
			for include in d.includes:
				if type(include) is LibraryInclude:
					inc_path = Path.joinpath(d.directory, include.filename) if full_path else include.filename
					all_includes.append(inc_path)

		for p in self.parameters:
			for include in p.includes:
				if type(include) is LibraryInclude:
					inc_path = Path.joinpath(p.directory, include.filename) if full_path else include
					all_includes.append(inc_path)

		return set(all_includes)

	def includes(self, full_path):
		
		all_includes = []
		for d in self.devices:
			for include in d.includes:
				inc_path = Path.joinpath(d.directory, include) if full_path else include
				all_includes.append(inc_path)

		for p in self.parameters:
			for include in p.includes:
				inc_path = Path.joinpath(p.directory, include) if full_path else include
				all_includes.append(inc_path)

		return set(all_includes)

	def sources(self, full_path):
		
		all_sources = []
		for d in self.devices:
			for src in d.sources:
				src_path = Path.joinpath(d.directory, src) if full_path else src
				all_sources.append(src_path)

		for p in self.parameters:
			for src in p.sources:
				src_path = Path.joinpath(p.directory, src) if full_path else src
				all_sources.append(src_path)

		return set(all_sources)

	def custom_code_paths(self, path=None):
		
		all_sources = []
		for src in self.custom_code:
			src_path = Path.joinpath(path, src) if path else src
			all_sources.append(src_path)

		return set(all_sources)