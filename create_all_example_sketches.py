""" create_all_example_sketches.py

Usage:
    create_all_example_sketches.py all [-v]
    create_all_example_sketches.py devices [-v]
    create_all_example_sketches.py parameters [-v]
    create_all_example_sketches.py modules [-v]

Options:
    -v, --verbose  Output extra logging information

"""

import sys
import os
import subprocess
import logging
import docopt

from pathlib import Path

from adl_runner import run

WINDOWS_PATH = Path("C:\\Program Files (x86)\\Arduino\\arduino.exe")

def find_arduino_executable():
    if WINDOWS_PATH.exists():
        return str(WINDOWS_PATH)

    #TODO: use which to find linux path
    return "/opt/bin/arduino-1.8.5/arduino"

def get_cmd_args(arduino_executable, sketch_path):
    return [arduino_executable, "--board", "arduino:avr:uno", "--verify", sketch_path]

def find_sketchbook_path():
    POSSIBLE_SKETCHBOOK_PATHS = ["~/sketchbook", "~/Arduino", "~/Documents/Arduino"]
    for possible_sketchbook_path in POSSIBLE_SKETCHBOOK_PATHS:
        candidate = Path(possible_sketchbook_path).expanduser()
        if candidate.exists():
            return candidate
    
    return None

if __name__ == "__main__":

    args = docopt.docopt(__doc__)

    example_files = []

    sketchbook_path = find_sketchbook_path()

    if sketchbook_path is None:
        print("No sketchbook found")
        sys.exit(1)

    if (args["--verbose"]):
        logging.basicConfig(level=logging.INFO)
    else:
        logging.basicConfig(level=logging.WARNING)

    if args["all"]:
        targets = ["devices", "parameters", "modules"]
    else:
        targets = [next(x for x in args if x in ["devices", "parameters", "modules"] and args[x])]

    for target in targets:
        xml_files = []
        for root, directories, files in os.walk("adl/{}".format(target)):
            xml_files += [Path.joinpath(Path(root), Path(f)) for f in files if f == "example.xml"]
        print("Found {} {}".format(len(xml_files), target))
        example_files += xml_files

    for example in example_files:
        print("Trying to build {}".format(example))
        board, adl_config = run(example, sketchbook_path)
        sketch_path = board.sketch_path()
        sketch_path = sketchbook_path.joinpath(sketch_path)
        try:
            args = get_cmd_args(find_arduino_executable(), str(sketch_path))
            res = subprocess.run(args, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            if len(res.stderr):
                print(res.stderr.decode("utf-8"))
        except subprocess.CalledProcessError as e:
            print("Out: " + e.output.decode("utf-8"))
            print("Std: " + e.stdout.decode("utf-8"))
            print("Err: " + e.stderr.decode("utf-8"))
            sys.exit(1)
        except:
            print("Attempted command: '{}'".format(" ".join(args)))
            raise

        