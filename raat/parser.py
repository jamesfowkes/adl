import os
import sys

import xml.etree.ElementTree as ET
import yaml

from collections import namedtuple

import raat.config
import raat.devices
import raat.types

import raat.overrides

import logging


def get_logger():
    return logging.getLogger(__name__)

VALID_FILETYPES = [".xml", ".yaml", ".json"]

def parse_file(filename, filetype=None, overrides=None):

    if filetype is None:
        filetype = filename.suffix

        if filetype not in VALID_FILETYPES:
            get_logger().error("Could not identify filetype of %s (got %s)", filename, filetype)
            return None

    if filetype not in VALID_FILETYPES:
        get_logger().error("filetype %s not valid (expected one of %s)", filetype, ", ".join(VALID_FILETYPES))
        return None

    get_logger().info("Parsing %s as %s", filename, filetype)

    if filetype == ".xml":
        tree = ET.parse(str(filename))
        board = raat.types.Board.from_xml(tree)

    elif filetype == ".yaml":
        stream = open(filename, 'r')
        board = raat.types.Board.from_yaml(yaml.load(stream))

    if overrides:
        board = raat.overrides.apply_overrides(overrides, board)

    get_logger().info("Found board '%s', type '%s'", board.name, board.type)

    devices = raat.devices.get(board.devices)
    parameters = raat.parameters.get(board.parameters)
    modules = raat.modules.get(board.modules)
    return raat.boards.get(board, devices, parameters, modules), raat.config.get(board, filename)
