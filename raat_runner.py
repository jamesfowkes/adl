""" raat.py

Usage:
    raat.py (--make|--build|--upload)... [--override=<target:value>]... [--port=<port>] <input_file> [--use_sketchbook] [--sketchbook=<parent_directory>] [--profile-size]

"""

import docopt
import logging
import os
from pathlib import Path

import xml.etree.ElementTree as ET

import raat
import raat.parser
import raat.devices
import raat.boards
import raat.parameters

import arduino_cli_interface

import subprocess

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


def profile_sketch(board, sketch_directory):
    elf_file = str(sketch_directory / (board.sanitised_name() + ".elf"))
    with open(sketch_directory / (board.sanitised_name() + ".prof"), "w") as f:
        args = ["avr-nm", "--print-size", "--reverse-sort", "--size-sort", elf_file]
        result = subprocess.run(args, stdout=f)
    return result


def make(board, raat_config, sketchbook):

    if sketchbook:

        directory = Path(sketchbook)
        sketch_path = board.sketch_path()

        sketch_directory = create_sketch_directory(directory, sketch_path.parent)
        raat.write_library(sketch_directory, raat_config, board)
        raat.write_sources(sketch_directory, board.raat_sources(True))
        raat.write_sources(sketch_directory, board.raat_includes(True))
        raat.write_sources(sketch_directory, board.device_includes(True))
        raat.write_sources(sketch_directory, board.device_sources(True))
        raat.write_sources(sketch_directory, board.parameter_includes(True))
        raat.write_sources(sketch_directory, board.parameter_sources(True))
        raat.write_sources(sketch_directory, board.module_includes(True))
        raat.write_sources(sketch_directory, board.module_sources(True))
        raat.write_sources(sketch_directory, board.board_sources(True))
        raat.write_sources(sketch_directory, board.custom_code_paths(raat_config.source_path))
        raat.write_board_support_package(sketch_directory, raat_config, board)
        raat.write_main(sketch_directory, sketch_path.name, raat_config, board)

    return board, raat_config, sketch_directory


if __name__ == "__main__":

    args = docopt.docopt(__doc__)

    logging.basicConfig(level=logging.INFO)
    raat.set_log_level(logging.INFO)
    raat.devices.activate_all()
    raat.boards.activate_all()
    raat.parameters.activate_all()
    raat.modules.activate_all()

    input_file = Path(args["<input_file>"])

    if args["--sketchbook"] is not None:
        sketchbook_path = Path(args["--sketchbook"]).expanduser()
    elif args["--use_sketchbook"]:
        sketchbook_path = os.getenv("RAAT_ARDUINO_SKETCHBOOK")
        if sketchbook_path is None:
            raise Exception("RAAT_ARDUINO_SKETCHBOOK environment variable must be set to use --use_sketchbook option")
    else:
        sketchbook_path = input_file.parent

    try:
        board, raat_config = raat.parser.parse_file(input_file, None, args.get("--override", None))
    except ET.ParseError:
        get_module_logger().error("Error parsing {}".format(str(input_file)))
        raise

    get_module_logger().info("Custom code directory: {}".format(raat_config.source_path))

    cli = arduino_cli_interface.ArduinoCLIInterface()

    if args["--make"]:
        make(board, raat_config, sketchbook_path)

    if args["--build"]:
        sketch_directory = get_sketch_directory(sketchbook_path, board.sketch_path().parent)
        cli.verify(board, sketch_directory)
        if args["--profile-size"]:
            profile_sketch(board, sketch_directory)

    if args["--upload"]:
        port = args.get("--port", None)
        sketch_directory = get_sketch_directory(sketchbook_path, board.sketch_path().parent)
        cli.upload(board, sketch_directory, port)
