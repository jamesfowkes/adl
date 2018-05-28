""" create_all_example_sketches.py

Usage:
    create_all_example_sketches.py [-v]

Options:
    -v, --verbose  Output extra logging information

"""

import sys
import os
import subprocess
import logging
import docopt

from adl_runner import run

def get_cmd_args(sketch_path):
    return ["/opt/bin/arduino-1.8.5/arduino", "--board", "arduino:avr:uno", "--verify", sketch_path]

if __name__ == "__main__":

    args = docopt.docopt(__doc__)

    example_files = []
    sketchbook_path = os.path.expanduser("~/sketchbook")

    if (args["--verbose"]):
        logging.basicConfig(level=logging.INFO)
    else:
        logging.basicConfig(level=logging.WARNING)

    for root, directories, files in os.walk("adl/devices"):
        xml_files = [os.path.join(root, f) for f in files if f == "example.xml"]
        example_files += xml_files  

    for example in example_files:
        print("Trying to build {}".format(example))
        board, adl_config = run(example, sketchbook_path)
        sketch_path = board.sketch_name()
        sketch_path = os.path.join(sketchbook_path, sketch_path.full_path)
        try:
            res = subprocess.run(get_cmd_args(sketch_path), check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        except subprocess.CalledProcessError as e:
            print("Out: " + e.output.decode("utf-8"))
            print("Std: " + e.stdout.decode("utf-8"))
            print("Err: " + e.stderr.decode("utf-8"))
            sys.exit(1)
        except:
            raise

        