""" adl.py

Usage:
	adl.py <input_file> [--sketchbook=<parent_directory>]

"""

import docopt
import adl
import adl.parser
import adl.devices
import adl.boards
import adl.parameters
import logging
import os

from pathlib import Path

THIS_PATH = Path(__file__).parent

def get_module_logger():
	return logging.getLogger(__name__)

def create_sketch_directory(parent_directory, sketch_directory):
	parent_directory = Path(parent_directory).expanduser()
	target_directory = Path.joinpath(parent_directory, sketch_directory)

	get_module_logger().info("Creating sketch directory '%s'", target_directory)

	if not target_directory.exists():
		os.makedirs(str(target_directory))
	else:
		for file in target_directory.iterdir():
			os.unlink(str(file))

	return target_directory

def write_sketch_to_directory(directory, sketch_name, sketch_contents):

	target = directory.joinpath(sketch_name)
	get_module_logger().info("Writing sketch '%s'", target)
	with target.open('w') as sketch:
		sketch.write(sketch_contents)

def run(input_file, sketchbook=None):

	input_file_path = Path.resolve(Path(input_file).parent)
	get_module_logger().info("Custom code directory: {}".format(input_file_path))

	board, adl_config = adl.parser.parse_file(Path(input_file))

	if sketchbook:
		directory = Path(sketchbook)
		sketch_path = board.sketch_path()

		sketch_directory = create_sketch_directory(directory, sketch_path.parent)
		write_sketch_to_directory(sketch_directory, sketch_path.name, board.code)
		adl.write_library(sketch_directory, adl_config, board)
		adl.write_sources(sketch_directory, board.adl_sources(True))
		adl.write_sources(sketch_directory, board.adl_includes(True))
		adl.write_sources(sketch_directory, board.device_includes(True))
		adl.write_sources(sketch_directory, board.device_sources(True))
		adl.write_sources(sketch_directory, board.parameter_includes(True))
		adl.write_sources(sketch_directory, board.parameter_sources(True))
		adl.write_sources(sketch_directory, board.custom_code_paths(input_file_path))

	return board, adl_config

if __name__ == "__main__":

	args = docopt.docopt(__doc__)

	logging.basicConfig(level=logging.INFO)
	adl.set_log_level(logging.INFO)
	adl.devices.activate_all()
	adl.boards.activate_all()
	adl.parameters.activate_all()

	run(args["<input_file>"], args["--sketchbook"])
