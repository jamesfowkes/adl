import logging
import shutil
import os

from pathlib import Path

from collections import namedtuple

import adl.devices
import adl.boards
import adl.parameters
import adl.template_engine

THIS_PATH = Path(__file__).parent

ADL_SOURCE_FILES = [
	("adl.cpp", "adl.cpp"),
	("adl-util.cpp", "adl-util.cpp"),
	("adl.h", "adl.h",),
	("adl-util.h", "adl-util.h"),
	("adl_defs.tpl", "adl_defs.h")
]

def get_module_logger():
	return logging.getLogger(__name__)

def get_subfolders(path):

	def absolute_path(d):
		return THIS_PATH.joinpath("adl_code", d)

	return [d for d in os.listdir(path) if absolute_path(d).is_dir()]

VALID_PROTOCOLS = get_subfolders(THIS_PATH.joinpath("adl_code"))

def write_file(template_file, target_directory, target_file, adl_config, board, protocol_dir=None):
	if protocol_dir is None:
		protocol_dir = Path(adl_config.protocol)

	rendered_code = adl.template_engine.render_library(protocol_dir.joinpath(template_file), adl_config, board)
	with open(target_directory.joinpath(target_file), 'w') as f:
		get_module_logger().info("Writing file %s to %s", target_file, target_directory)
		f.write(rendered_code)

def copy_file(relative_src_path, target_directory):
	filename = relative_src_path.name
	src_path = THIS_PATH.joinpath(relative_src_path)
	dst_path = target_directory.joinpath(filename)
	shutil.copy(src_path, dst_path)

def write_library(target_directory, adl_config, board):
	protocol_src_path = THIS_PATH.joinpath("adl_code", adl_config.protocol)
	get_module_logger().info("Using protocol from {}".format(protocol_src_path))

	for file in os.listdir(protocol_src_path):
		if file.endswith(".h") or file.endswith(".cpp") or file.endswith(".c"):
			write_file(file, target_directory, file, adl_config, board)

	copy_file(Path("devices/device.h"), target_directory)
	copy_file(Path("parameters/parameter.h"), target_directory)

	for template_file, target_file in ADL_SOURCE_FILES:
		write_file(template_file, target_directory, target_file, adl_config, board, Path(""))

def write_sources(target_directory, sources):
	for src in sources:
		copy_file(src, target_directory)

def set_log_level(level):
	logging.getLogger("parser").setLevel(level)
	adl.devices.set_log_level(level)
	adl.boards.set_log_level(level)
	adl.parameters.set_log_level(level)
