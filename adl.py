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

def get_module_logger():
	return logging.getLogger(__name__)

def sanitise_sketch_name(name):

	if name[0].isdigit():
		get_module_logger().warning("Name starts with numeric value. Prefixing with underscore.")
		name = "_" + name

	if " " in name:
		get_module_logger().warning("Name contains spaces. Replacing with underscores.")
		name = name.replace(" ", "_")

	return name

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

if __name__ == "__main__":

	args = docopt.docopt(__doc__)

	logging.basicConfig(level=logging.INFO)
	adl.set_log_level(logging.INFO)
	adl.devices.activate_all()
	adl.boards.activate_all()
	adl.parameters.activate_all()

	board, adl_config = adl.parser.parse_file(args["<input_file>"])

	if args["--sketchbook"]:
		directory = args["--sketchbook"]
		sketch_name = sanitise_sketch_name(board.name)

		sketch_directory = create_sketch_directory(directory, sketch_name)
		write_sketch_to_directory(sketch_directory, sketch_name+".ino", board.code)
		adl.write_library(sketch_directory, adl_config)
		adl.write_sources(sketch_directory, board.includes("devices"))
		adl.write_sources(sketch_directory, board.sources("devices"))
