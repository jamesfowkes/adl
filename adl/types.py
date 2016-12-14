from collections import namedtuple

class Pin(namedtuple("Pin", ["name", "number", "io"])):
	__slots__ = ()

	@classmethod
	def from_xml(cls, pin_node):
		return cls(pin_node.attrib["name"], pin_node.attrib["number"], pin_node.attrib.get("io", ""))

	@classmethod
	def from_yaml(cls, pin_dict):
		return cls(pin_dict["name"], pin_dict["number"], pin_dict.get("io", ""))

class Device(namedtuple("Device", ["name", "type", "pins"])):
	__slots__ = ()

	@classmethod
	def from_xml(cls, device_node):
		name = device_node.attrib["name"]
		device_type = device_node.attrib["type"]
		pins = [Pin.from_xml(pin_node) for pin_node in device_node.findall("pin")]

		return cls(name, device_type, pins)

	@classmethod
	def from_yaml(cls, device_dict):
		name = device_dict["name"]
		device_type = device_dict["type"]
		pins = [Pin.from_yaml(pin) for pin in device_dict["pins"]]

		return cls(name, device_type, pins)

class Board(namedtuple("Board", ["type", "name", "devices", "info", "adl", "attrs"])):
	__slots__ = ()

	@classmethod
	def from_xml(cls, node):
		board_node = node.find(".")
		name = board_node.attrib["name"]
		board_type = board_node.attrib["type"]
		info = board_node.find("info").text
		devices = [Device.from_xml(node) for node in node.find("devices")]
		adl = board_node.find("adl")
		return cls(board_type, name, devices, info, adl, board_node.attrib)

	@classmethod
	def from_yaml(cls, board_dict):
		board_type = board_dict["board"]["type"]
		name = board_dict["board"]["name"]
		devices = [Device.from_yaml(dev) for dev in board_dict["board"]["devices"]]
		info = board_dict["board"].get("info", "")
		adl = board_dict["board"].get("adl", {})
		return cls(board_type, name, devices, info, adl, board_dict["board"])
