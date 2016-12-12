import os

import xml.etree.ElementTree as ET
import yaml

from collections import namedtuple

import adl
import adl.devices
import adl.types

import logging

def get_type_from_filename(filename):
	return os.path.splitext(filename)[1][1:]

def parse_file(filename, filetype=None):

	if filetype is None:
		filetype = get_type_from_filename(filename)

		if filetype not in ["xml", "yaml", "json"]:
			logging.getLogger("parser").info("Could not identify filetype of %s", filename)

	if filetype == "xml":
		tree = ET.parse(filename)
		board = adl.types.Board.from_xml(tree)

	if filetype == "yaml":
		stream = open(filename, 'r')
		board = adl.types.Board.from_yaml(yaml.load(stream))

	logging.getLogger("parser").info("Found board '%s', type '%s'", board.name, board.type)

	return adl.boards.get(board, adl.devices.get(board.devices))
