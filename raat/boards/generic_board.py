import os
import logging
import itertools

from collections import namedtuple
from orderedset import OrderedSet

from pathlib import Path

import raat
from raat.types import RAATSource, RAATInclude
from raat.types import ParameterSource, ParameterInclude
from raat.types import DeviceSource, DeviceInclude
from raat.types import LocalSource, LocalInclude
from raat.types import ModuleSource, ModuleInclude
from raat.types import LibraryInclude
from raat.types import SourceFileProvider

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

def get_paths(dependencies, use_full_path):
    paths = []
    for dep in dependencies:
        path = dep if use_full_path else dep.name
        paths.append(path)

    return paths

def dependencies_by_type(component_list, dependencies, use_full_path):
    all_paths = []
    try:
        _ = iter(dependencies)
    except TypeError:
        dependencies = [dependencies]

    for dependency in dependencies:
        for component in component_list:
            incs_and_srcs = component.get_sources(dependency) + component.get_includes(dependency)
            all_paths.extend(get_paths(incs_and_srcs, use_full_path))

    return OrderedSet(all_paths)

class GenericBoard(SourceFileProvider):

    sources = []
    includes = []

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

    def all_components(self):
        return [self] + self.devices + self.parameters + self.modules

    def bsp_components(self):
        return [self.nonvolatile, self.serial]

    def raat_sources(self, use_full_path):
        sources = dependencies_by_type(self.all_components(), RAATSource, use_full_path)
        return [raat.codepath().joinpath(src) for src in sources] if use_full_path else sources

    def raat_includes(self, use_full_path):
        includes = dependencies_by_type(self.all_components(), RAATInclude, use_full_path)
        return [raat.codepath().joinpath(inc) for inc in includes] if use_full_path else includes

    def parameter_includes(self, use_full_path):
        return dependencies_by_type(self.parameters, ParameterInclude, use_full_path)

    def parameter_sources(self, use_full_path):
        return dependencies_by_type(self.parameters, ParameterSource, use_full_path)

    def device_includes(self, use_full_path):
        return dependencies_by_type(self.devices, (DeviceInclude, ModuleInclude, ParameterInclude), use_full_path)

    def device_sources(self, use_full_path):
        return dependencies_by_type(self.devices, (DeviceSource, ModuleSource, ParameterSource), use_full_path)

    def module_includes(self, use_full_path):
        return dependencies_by_type(self.modules, ModuleInclude, use_full_path)

    def module_sources(self, use_full_path):
        return dependencies_by_type(self.modules, ModuleSource, use_full_path)

    def library_includes(self, use_full_path):
        return dependencies_by_type(self.all_components(), LibraryInclude, use_full_path)

    def board_sources(self, use_full_path):
        return dependencies_by_type(self.bsp_components(), LocalSource, use_full_path)
        
    def required_libraries(self):
        required_libraries = [self.arduino_libs] + [d.required_libraries for d in self.devices]
        return set(list(itertools.chain.from_iterable(required_libraries)))
        
    def custom_code_paths(self, path=None):
        
        all_sources = []
        for src in self.custom_code:
            src_path = Path.joinpath(path, src) if path else src
            all_sources.append(src_path)

        return set(all_sources)
