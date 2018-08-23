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

	def update(self, new_value):
		return Setting(self.id, self.name, new_value)
		
	def check(self, check_fn, exception_str):
		if not check_fn(self.value):
			raise Exception(exception_str)

	def parse(self, parser):
		return self.update(parser(self.value))

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

class Parameter(namedtuple("Parameter", ["name", "type", "settings"])):

	__slots__ = ()

	@classmethod
	def from_xml(cls, parameter_node):
		name = parameter_node.attrib["name"]
		parameter_type = parameter_node.attrib["type"]
		settings = [Setting.from_xml(setting_node) for setting_node in parameter_node.findall("setting")]
		settings_dict = {setting.id : setting for setting in settings}

		return cls(name, parameter_type, settings_dict)

class Board(namedtuple("Board", ["type", "name", "devices", "parameters", "settings", "info", "adl", "custom_code", "attrs"])):
	__slots__ = ()

	@classmethod
	def from_xml(cls, node):
		board_node = node.find(".")
		name = board_node.attrib["name"]
		board_type = board_node.attrib["type"]
		info = board_node.find("info").text
		
		devices = node.find("devices") or []
		devices = [Device.from_xml(node) for node in devices]
		
		settings = node.findall("setting") or []
		settings = [Setting.from_xml(node) for node in settings]
		settings_dict = {setting.id : setting for setting in settings}

		parameters = node.find("parameters") or []
		parameters = [Parameter.from_xml(node) for node in parameters]

		custom_code = board_node.find("custom_code")
		if custom_code:
			filenames = [f.text for f in custom_code.findall("file")]
		else:
			filenames = []

		adl = board_node.find("adl")
		if adl is None:
			adl = {}

		return cls(board_type, name, devices, parameters, settings_dict, info, adl, filenames, board_node.attrib)

	@classmethod
	def from_yaml(cls, board_dict):
		board_type = board_dict["board"]["type"]
		name = board_dict["board"]["name"]
		devices = [Device.from_yaml(dev) for dev in board_dict["board"]["devices"]]
		
		if "settings" in board_dict["board"]:
			settings = [Setting.from_yaml(setting) for setting in board_dict["board"]["settings"]]
			settings_dict = {setting.id : setting for setting in settings}
		else:
			settings_dict = {}
		
		if "custom_code" in board_dict["board"]:
			filenames = board_dict["board"]["custom_code"]
		else:
			filenames = []

		info = board_dict["board"].get("info", "")
		adl = board_dict["board"].get("adl", {})
		return cls(board_type, name, devices, settings_dict, info, adl, filenames, board_dict["board"])

class LocalInclude:
	def __init__(self, filename):
		self.filename = filename
	

class LibraryInclude:
	def __init__(self, filename):
		self.filename = filename

