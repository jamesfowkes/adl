from pathlib import Path

from collections import namedtuple, Counter

import adl

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

	def parse(self, parse_function):
		return self.update(parse_function(self.value))

	def check(self, check_function, error_msg):
		if not check_function(self.value):
			raise Exception(error_msg)

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

class LoggingModule(namedtuple("LoggingModule", ["name", "prefix"])):

	__slots__ = ()

	@classmethod
	def from_xml(cls, log_module_node):
		name = log_module_node.text
		prefix = log_module_node.attrib.get("prefix", name[0:3])
		return cls(name, prefix)

	def c_name(self):
		return "s_%d".format(self.name.lower())

def get_unique_log_modules(nodes):

	prefixes = [node.attrib.get("prefix", node.text[0:3]) for node in nodes]
	
	if len(set(prefixes)) < len(prefixes):
		counter = Counter()
		unique_prefixes = []
		for prefix in prefixes:
			if (counter[prefix] == 0):
				unique_prefixes.append(prefix)
			else:
				unique_prefixes.append("{}_{}".format(prefix, counter[prefix]+1))

			counter[prefix] += 1
	else:
		unique_prefixes = prefixes
		
	return [LoggingModule(node.text, prefix) for (node, prefix) in zip(nodes, unique_prefixes)]


class Board(namedtuple("Board", ["type", "name", "devices", "parameters", "settings", "info", "adl", "custom_code", "attrs", "log_modules"])):
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

		log_modules = get_unique_log_modules(node.find("logging") or [])

		custom_code = board_node.find("custom_code")
		if custom_code:
			custom_code_filenames = [f.text for f in custom_code.findall("file")]
		else:
			custom_code_filenames = []

		adl = board_node.find("adl")
		if adl is None:
			adl = {}

		return cls(board_type, name, devices, parameters, settings_dict, info, adl,
			custom_code_filenames, board_node.attrib, log_modules)

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

class IncludeFile(Path):
	_flavour = Path('.')._flavour

class SourceFile(Path):
	_flavour = Path('.')._flavour

class ADLSource(SourceFile):
	pass

class ADLInclude(IncludeFile):
	pass

class LocalSource(SourceFile):
	pass

class LocalInclude(IncludeFile):
	pass

class LibraryInclude(IncludeFile):
	pass

class ParameterSource(SourceFile):
	pass

class ParameterInclude(IncludeFile):
	pass

class DeviceSource(SourceFile):
	pass

class DeviceInclude(IncludeFile):
	pass
	