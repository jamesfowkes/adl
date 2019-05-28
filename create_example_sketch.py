""" create_all_example_sketches.py

Usage:
    create_all_example_sketches.py <target> [-v] [--sketchbook=<sketchbook_path>]

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
    POSSIBLE_SKETCHBOOK_PATHS = ["~/sketchbook",
                                 "~/Arduino", "~/Documents/Arduino"]
    for possible_sketchbook_path in POSSIBLE_SKETCHBOOK_PATHS:
        candidate = Path(possible_sketchbook_path).expanduser()
        if candidate.exists():
            return candidate

    return None


if __name__ == "__main__":

    args = docopt.docopt(__doc__)

    target_example_name = args["<target>"]

    sketchbook_path = None

    if "--sketchbook" in args and args["--sketchbook"]:
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

    found_example = False
    for possible_target_type in ["devices", "parameters", "modules"]:
        for root, directories, files in os.walk("raat/{}".format(possible_target_type)):
            if target_example_name in root:
                for f in files:
                    if f == "example.xml":
                        found_example = Path.joinpath(Path(root), Path(f))
                        print("Found {}".format(str(found_example)))
                        break

    if found_example:
        print("Trying to build {}".format(found_example))
        board, raat_config = parser.parse_file(Path(found_example))
        make(board, raat_config, sketchbook_path)

        sketch_directory = get_sketch_directory(
            sketchbook_path, board.sketch_path().parent)
        cli = arduino_cli_interface.ArduinoCLIInterface()
        cli.verify(board, sketch_directory)
    else:
        print("Could not find example for {}".format(target_example_name))
