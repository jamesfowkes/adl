import os
import sys

import xml.etree.ElementTree as ET
import yaml

from collections import namedtuple

import adl.config
import adl.devices
import adl.types

import logging

VALID_FILETYPES = ["xml", "yaml", "json"]
def get_type_from_filename(filename):
	return os.path.splitext(filename)[1][1:]

def parse_file(filename, filetype=None):

	if filetype is None:
		filetype = get_type_from_filename(filename)

		if filetype not in VALID_FILETYPES:
			logging.getLogger("parser").error("Could not identify filetype of %s", filename)
			return None

	if filetype not in VALID_FILETYPES:
		logging.getLogger("parser").error("filetype %s not valid (expected one of %s)", filetype, ", ".join(VALID_FILETYPES))
		return None

	logging.getLogger("parser").info("Parsing %s as %s", filename, filetype)

	if filetype == "xml":
		tree = ET.parse(filename)
		board = adl.types.Board.from_xml(tree)

	if filetype == "yaml":
		stream = open(filename, 'r')
		board = adl.types.Board.from_yaml(yaml.load(stream))

	logging.getLogger("parser").info("Found board '%s', type '%s'", board.name, board.type)

	return adl.boards.get(board, adl.devices.get(board.devices)), adl.config.get(board)
