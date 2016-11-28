import xml.etree.ElementTree as ET

import adl
import adl.devices
import logging

def get_board_name(board):
	return board.attrib["name"]

def get_device_type(device):
	return device.attrib["type"]

def get_devices(devices_node):

	return [adl.devices.get(get_device_type(device_node), device_node) for device_node in devices_node.findall("device")]

def parse_file(filename):
	tree = ET.parse(filename)

	board_name = get_board_name(tree.find("."))

	logging.getLogger("parser").info("Found board '%s'", board_name)

	devices = get_devices(tree.find("devices"))

	return adl.boards.get(board_name, devices)
