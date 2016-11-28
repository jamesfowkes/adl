""" adl.py

Usage:
	adp.py <input_file>
"""

import docopt
import adl
import adl.parser
import adl.devices
import adl.boards
import logging

if __name__ == "__main__":
	args = docopt.docopt(__doc__)

	logging.basicConfig(level=logging.INFO)
	adl.set_log_level(logging.INFO)
	adl.devices.activate_all()
	adl.boards.activate_all()

	board = adl.parser.parse_file(args["<input_file>"])

	print(board.code)
