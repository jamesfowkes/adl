""" create_all_example_sketches.py

Usage:
    create_all_example_sketches.py all [-v] [--sketchbook=<sketchbook_path>]
    create_all_example_sketches.py devices [-v] [--sketchbook=<sketchbook_path>]
    create_all_example_sketches.py parameters [-v] [--sketchbook=<sketchbook_path>]
    create_all_example_sketches.py modules [-v] [--sketchbook=<sketchbook_path>]
    create_all_example_sketches.py general [-v] [--sketchbook=<sketchbook_path>]

Options:
    -v, --verbose  Output extra logging information

"""

import sys
import os
import logging
import docopt

from pathlib import Path

from raat import parser
from raat_runner import make, get_sketch_directory
import arduino_cli_interface

def find_sketchbook_path():
    POSSIBLE_SKETCHBOOK_PATHS = ["~/sketchbook", "~/Arduino", "~/Documents/Arduino"]
    for possible_sketchbook_path in POSSIBLE_SKETCHBOOK_PATHS:
        candidate = Path(possible_sketchbook_path).expanduser()
        if candidate.exists():
            return candidate
    
    return None

POSSIBLE_TARGETS = {
    "devices" : Path("raat", "devices"),
    "parameters" : Path("raat", "parameters"),
    "modules" : Path("raat", "modules"),
    "general" : Path("examples")
}

if __name__ == "__main__":

    args = docopt.docopt(__doc__)

    example_files = []

    sketchbook_path = None

    if "--sketchbook" in args:
        sketchbook_path = Path(args["--sketchbook"]).expanduser()
    else:
        sketchbook_path = find_sketchbook_path()

    if sketchbook_path is None:
        print("No sketchbook found")
        sys.exit(1)

    if (args["--verbose"]):
        logging.basicConfig(level=logging.INFO)
    else:
        logging.basicConfig(level=logging.WARNING)

    if args["all"]:
        targets = POSSIBLE_TARGETS.keys()
    else:
        targets = [next(x for x in args if (x in POSSIBLE_TARGETS) and args[x])]

    for target in targets:
        xml_files = []
        target_path = POSSIBLE_TARGETS[target]
        for root, directories, files in os.walk("{}".format(target_path)):
            xml_files += [Path.joinpath(Path(root), Path(f)) for f in files if f == "example.xml"]
        print("Found {} {}".format(len(xml_files), target))
        example_files += xml_files

    for example in example_files:
        print("Trying to build {}".format(example))
        board, raat_config = parser.parse_file(Path(example))
        make(board, raat_config, sketchbook_path)

        sketch_directory = get_sketch_directory(sketchbook_path, board.sketch_path().parent)
        cli = arduino_cli_interface.ArduinoCLIInterface()
        if not cli.verify(board, sketch_directory):
            sys.exit(1)
