""" adl.py

Usage:
	adp.py <input_file> [--sketchbook=<parent_directory>]

"""

import docopt
import adl
import adl.parser
import adl.devices
import adl.boards
import adl.parameters
import logging
import os

THIS_DIRECTORY = os.path.dirname(__file__)

def get_module_logger():
	return logging.getLogger(__name__)

def create_sketch_directory(parent_directory, sketch_directory):
	parent_directory = os.path.expanduser(parent_directory)
	target_directory = os.path.join(parent_directory + "/" + sketch_directory)

	if not os.path.exists(target_directory):
		os.makedirs(target_directory)
	else:
		for file in os.listdir(target_directory):
			os.unlink(os.path.join(target_directory, file))

	return target_directory

def write_sketch_to_directory(directory, sketch_name, sketch_contents):

	target = os.path.join(directory, sketch_name)
	get_module_logger().info("Writing sketch '%s'", target)
	with open(target, 'w') as sketch:
		sketch.write(sketch_contents)

def run(input_file, sketchbook=None):

	input_file_path = os.path.abspath(os.path.dirname(input_file))
	get_module_logger().info("Custom code directory: {}".format(input_file_path))

	board, adl_config = adl.parser.parse_file(input_file)

	if sketchbook:
		directory = sketchbook
		sketch_name = board.sketch_name()

		sketch_directory = create_sketch_directory(directory, sketch_name.folder)
		write_sketch_to_directory(sketch_directory, sketch_name.full_name, board.code)

		adl.write_library(sketch_directory, adl_config, board)
		adl.write_sources(sketch_directory, board.adl_sources(True))
		adl.write_sources(sketch_directory, board.adl_includes(True))
		adl.write_sources(sketch_directory, board.device_includes(True))
		adl.write_sources(sketch_directory, board.sources(True))
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
