import logging
import shutil
import os

from collections import namedtuple

import adl.devices
import adl.boards
import adl.template_engine

THIS_PATH = os.path.dirname(__file__)

def write_library(directory, adl_config):
	src_path = os.path.join(THIS_PATH, "adl_code")
	for file in os.listdir(src_path):
		rendered_code = adl.template_engine.render_library(file, adl_config)
		with open(os.path.join(directory, file), 'w') as f:
			f.write(rendered_code)

def set_log_level(level):
	logging.getLogger("parser").setLevel(level)
	adl.devices.set_log_level(level)
	adl.boards.set_log_level(level)
