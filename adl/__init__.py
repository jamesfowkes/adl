import logging
import shutil
import os

import adl.devices
import adl.boards

THIS_PATH = os.path.dirname(__file__)

def copy_library(directory):
	code_path = os.path.join(THIS_PATH, "adl_code")
	for file in os.listdir(code_path):
		shutil.copy(os.path.join(code_path, file), directory)

def set_log_level(level):
	logging.getLogger("parser").setLevel(level)
	adl.devices.set_log_level(level)
	adl.boards.set_log_level(level)
