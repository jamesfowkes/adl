import logging
import shutil
import os

from collections import namedtuple

import adl.devices
import adl.boards
import adl.template_engine

THIS_PATH = os.path.dirname(__file__)

def get_module_logger():
	return logging.getLogger(__name__)

def get_subfolders(path):

	def absolute_path(d):
		return os.path.join(THIS_PATH, "adl_code", d)

	return [d for d in os.listdir(path) if os.path.isdir(absolute_path(d))]

VALID_PROTOCOLS = get_subfolders(os.path.join(THIS_PATH, "adl_code"))

def write_file(file, target_directory, adl_config, board, protocol_dir=None):
	if protocol_dir is None:
		protocol_dir = adl_config.protocol

	rendered_code = adl.template_engine.render_library(os.path.join(protocol_dir, file), adl_config, board)
	with open(os.path.join(target_directory, file), 'w') as f:
		f.write(rendered_code)

def copy_file(relative_src_path, target_directory):
	filename = os.path.split(relative_src_path)[-1]
	src_path = os.path.join(THIS_PATH, relative_src_path)
	dst_path = os.path.join(target_directory, filename)
	shutil.copy(src_path, dst_path)

def write_library(target_directory, adl_config, board):
	src_path = os.path.join(THIS_PATH, "adl_code", adl_config.protocol)

	get_module_logger().info("Using protocol from {}".format(src_path))

	for file in os.listdir(src_path):
		write_file(file, target_directory, adl_config, board)

	copy_file("devices/device.h", target_directory)

	write_file("adl.cpp", target_directory, adl_config, board, "")
	write_file("adl.h", target_directory, adl_config, board, "")

def write_sources(target_directory, sources):
	for src in sources:
		copy_file(src, target_directory)

def set_log_level(level):
	logging.getLogger("parser").setLevel(level)
	adl.devices.set_log_level(level)
	adl.boards.set_log_level(level)
