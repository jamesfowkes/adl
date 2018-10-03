""" adl.py

Usage:
	adl.py (--make|--build|--upload)... [--override=<target:value>]... [--port=<port>] <input_file> [--sketchbook=<parent_directory>]

"""

import docopt
import logging
import os
from pathlib import Path

import adl
import adl.parser
import adl.devices
import adl.boards
import adl.parameters

from arduino_cli_interface import verify, upload

THIS_PATH = Path(__file__).parent

def get_module_logger():
	return logging.getLogger(__name__)

def get_sketch_directory(parent_directory, sketch_directory):
	parent_directory = Path(parent_directory).expanduser()
	target_directory = Path.joinpath(parent_directory, sketch_directory)
	return target_directory

def create_sketch_directory(parent_directory, sketch_directory):
	target_directory = get_sketch_directory(parent_directory, sketch_directory)

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

def make(board, adl_config, sketchbook):

	if sketchbook:

		directory = Path(sketchbook)
		sketch_path = board.sketch_path()

		sketch_directory = create_sketch_directory(directory, sketch_path.parent)
		adl.write_library(sketch_directory, adl_config, board)
		adl.write_sources(sketch_directory, board.adl_sources(True))
		adl.write_sources(sketch_directory, board.adl_includes(True))
		adl.write_sources(sketch_directory, board.device_includes(True))
		adl.write_sources(sketch_directory, board.device_sources(True))
		adl.write_sources(sketch_directory, board.parameter_includes(True))
		adl.write_sources(sketch_directory, board.parameter_sources(True))
		adl.write_sources(sketch_directory, board.custom_code_paths(adl_config.source_path))
		write_sketch_to_directory(sketch_directory, sketch_path.name, board.code(adl_config))

	return board, adl_config, sketch_directory

if __name__ == "__main__":

	args = docopt.docopt(__doc__)

	logging.basicConfig(level=logging.INFO)
	adl.set_log_level(logging.INFO)
	adl.devices.activate_all()
	adl.boards.activate_all()
	adl.parameters.activate_all()

	input_file = args["<input_file>"]
	sketchbook_path = Path(args["--sketchbook"]).expanduser()

	board, adl_config = adl.parser.parse_file(Path(input_file), None, args.get("--override", None))

	get_module_logger().info("Custom code directory: {}".format(adl_config.source_path))

	if args["--make"]:
		make(board, adl_config, sketchbook_path)

	if args["--build"]:
		sketch_directory = get_sketch_directory(sketchbook_path, board.sketch_path().parent)
		verify(board, sketch_directory)

	if args["--upload"]:
		port = args.get("--port", None)
		sketch_directory = get_sketch_directory(sketchbook_path, board.sketch_path().parent)
		upload(board, sketch_directory, port)
