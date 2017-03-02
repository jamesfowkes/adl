from collections import namedtuple

class Setting(namedtuple("Setting", ["id", "name", "value"])):

	__slots__ = ()

	@classmethod
	def from_xml(cls, setting_node):
		dev_id = setting_node.attrib["id"]
		name = setting_node.attrib.get("name", "")
		value = setting_node.attrib["value"]

		return cls(dev_id, name, value)

	@classmethod
	def from_yaml(cls, setting_dict):
		dev_id = setting_dict["id"]
		name = setting_dict.get("name", "")
		value = setting_dict["value"]
		
		return cls(dev_id, name, value)

class Device(namedtuple("Device", ["name", "type", "settings"])):

	__slots__ = ()

	@classmethod
	def from_xml(cls, device_node):
		name = device_node.attrib["name"]
		device_type = device_node.attrib["type"]
		settings = [Setting.from_xml(setting_node) for setting_node in device_node.findall("setting")]
		settings_dict = {setting.id : setting for setting in settings}

		return cls(name, device_type, settings_dict)

	@classmethod
	def from_yaml(cls, device_dict):
		name = device_dict["name"]
		device_type = device_dict["type"]
		settings = [Setting.from_yaml(setting) for setting in device_dict["setting"]]
		settings_dict = {setting.id : setting for setting in settings}

		return cls(name, device_type, settings_dict)

class Board(namedtuple("Board", ["type", "name", "devices", "settings", "info", "adl", "attrs"])):
	__slots__ = ()

	@classmethod
	def from_xml(cls, node):
		board_node = node.find(".")
		name = board_node.attrib["name"]
		board_type = board_node.attrib["type"]
		info = board_node.find("info").text
		devices = [Device.from_xml(node) for node in node.find("devices")]
		
		settings = [Setting.from_xml(node) for node in node.findall("setting")]
		settings_dict = {setting.id : setting for setting in settings}

		adl = board_node.find("adl")
		return cls(board_type, name, devices, settings_dict, info, adl, board_node.attrib)

	@classmethod
	def from_yaml(cls, board_dict):
		board_type = board_dict["board"]["type"]
		name = board_dict["board"]["name"]
		devices = [Device.from_yaml(dev) for dev in board_dict["board"]["devices"]]
		
		settings = [Setting.from_yaml(setting) for setting in board_dict["board"]["settings"]]
		settings_dict = {setting.id : setting for setting in settings}
		
		info = board_dict["board"].get("info", "")
		adl = board_dict["board"].get("adl", {})
		return cls(board_type, name, devices, settings_dict, info, adl, board_dict["board"])
