import xml.etree.ElementTree as ET

import adl
import adl.devices
import logging

def get_devices(devices_node):
	return [adl.devices.get(device_node.attrib["type"], device_node) for device_node in devices_node.findall("device")]

def parse_file(filename):
	tree = ET.parse(filename)
	board = tree.find(".")

	logging.getLogger("parser").info("Found board '%s', type '%s'", board.attrib["name"], board.attrib["type"])

	devices = get_devices(tree.find("devices"))

	return adl.boards.get(board, devices)
