from pathlib import Path

from collections import namedtuple, Counter


def flatten(l):

    flat = []
    for el in l:
        if type(el) is list:
            flat.extend(el)
        else:
            flat.append(el)
    return flat


class IncludeFile(Path):
    _flavour = Path('.')._flavour


class SourceFile(Path):
    _flavour = Path('.')._flavour


class RAATSource(SourceFile):
    pass


class RAATInclude(IncludeFile):
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


class ModuleSource(SourceFile):
    pass


class ModuleInclude(IncludeFile):
    pass


class SourceFileProvider:

    def get_sources(self, target_type):
        return [s for s in self.sources if isinstance(s, target_type)]

    def get_includes(self, target_type):
        return [s for s in self.includes if isinstance(s, target_type)]


class Setting(namedtuple("Setting", ["id", "name", "value"])):

    __slots__ = ()

    @classmethod
    def from_xml(cls, setting_node, count):
        dev_id = setting_node.attrib["id"]
        name = setting_node.attrib.get("name", "")
        if count == 0:
            value = setting_node.attrib["value"]
        else:
            if "values" in setting_node.attrib:
                value = setting_node.attrib["values"].split("|")
            elif "all_values" in setting_node.attrib:
                value = [setting_node.attrib["all_values"]] * count
            else:
                raise Exception("Expected 'values' or 'all_values' attribute for multiple settings")

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

    @staticmethod
    def make_group(settings_dict, expected_count):
        counts = [len(setting.value) for setting in settings_dict.values()]
        if not len(set(counts)) == 1 or counts[0] != expected_count:
            raise Exception("Expected all setting lengths to be {}!".format(expected_count))

        count = counts[0]

        settings_list = []
        for i in range(0, count):
            new_settings_dict = {}
            for setting in settings_dict.values():
                new_settings_dict[setting.id] = Setting(setting.id, setting.name, setting.value[i])
            settings_list.append(new_settings_dict)

        return settings_list


class Devices(namedtuple("Devices", ["single", "grouped"])):

    __slots__ = ()

    @classmethod
    def from_xml_list(cls, device_xml_nodes):
        single_devices = []
        group_devices = []
        for node in device_xml_nodes:
            if "count" in node.attrib:
                group_devices.append(DeviceGroup.from_xml(node, int(node.attrib["count"])))
            else:
                single_devices.append(Device.from_xml(node))

        return cls(single_devices, group_devices)


class Device(namedtuple("Device", ["name", "type", "settings"])):

    __slots__ = ()

    @classmethod
    def from_xml(cls, device_node):
        name = device_node.attrib["name"]
        device_type = device_node.attrib["type"]
        device_count = int(device_node.attrib.get("count", 0))
        settings = [Setting.from_xml(setting_node, device_count) for setting_node in device_node.findall("setting")]
        settings_dict = {setting.id: setting for setting in settings}
        return cls(name, device_type, settings_dict)

    @classmethod
    def from_yaml(cls, device_dict):
        name = device_dict["name"]
        device_type = device_dict["type"]
        settings = [Setting.from_yaml(setting) for setting in device_dict["setting"]]
        settings_dict = {setting.id: setting for setting in settings}

        return cls(name, device_type, settings_dict)


class DeviceGroup(namedtuple("Device", ["name", "type", "settings", "count"])):

    @classmethod
    def from_xml(cls, device_node, count):
        device = Device.from_xml(device_node)
        return cls(device.name, device.type, device.settings, count)


class Parameters(namedtuple("Parameters", ["single", "grouped"])):

    __slots__ = ()

    @classmethod
    def from_xml_list(cls, param_xml_nodes):
        single_params = []
        group_params = []
        for node in param_xml_nodes:
            if "count" in node.attrib:
                group_params.append(ParameterGroup.from_xml(node, int(node.attrib["count"])))
            else:
                single_params.append(Parameter.from_xml(node))

        return cls(single_params, group_params)


class Parameter(namedtuple("Parameter", ["name", "type", "settings"])):

    __slots__ = ()

    @classmethod
    def from_xml(cls, parameter_node):
        name = parameter_node.attrib["name"]
        parameter_type = parameter_node.attrib["type"]
        settings = [Setting.from_xml(setting_node, 0) for setting_node in parameter_node.findall("setting")]
        settings_dict = {setting.id: setting for setting in settings}
        return cls(name, parameter_type, settings_dict)


class ParameterGroup(namedtuple("Parameter", ["name", "type", "settings", "count"])):

    @classmethod
    def from_xml(cls, parameter_node, count):
        param = Parameter.from_xml(parameter_node)
        return cls(param.name, param.type, param.settings, count)


class LoggingModule(namedtuple("LoggingModule", ["name", "prefix"])):

    __slots__ = ()

    @classmethod
    def from_xml(cls, log_module_node):
        name = log_module_node.text
        prefix = log_module_node.attrib.get("prefix", name[0:3])
        return cls(name, prefix)

    def c_name(self):
        return "s_%d".format(self.name.lower())


class Module(namedtuple("Module", ["name"])):

    __slots__ = ()

    @classmethod
    def from_xml(cls, module_node):
        return cls(module_node.text)


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


class Board(namedtuple("Board", [
    "type", "name",
    "devices", "parameters",
    "modules", "settings", "info", "raat", "custom_code",
    "attrs", "log_modules", "defines", "arduino_libs"])
):
    __slots__ = ()

    @classmethod
    def from_xml(cls, node):
        board_node = node.find(".")
        name = board_node.attrib["name"]
        board_type = board_node.attrib["type"]

        devices = Devices.from_xml_list(node.find("devices") or [])
        parameters = Parameters.from_xml_list(node.find("parameters") or [])

        modules = node.find("modules") or []
        modules = [Module.from_xml(module_node) for module_node in modules]

        settings = node.findall("setting") or []
        settings = [Setting.from_xml(setting_node) for setting_node in settings]
        settings_dict = {setting.id: setting for setting in settings}

        info = board_node.find("info").text

        raat = board_node.find("raat")
        if raat is None:
            raat = {}

        custom_code = board_node.find("custom_code")
        if custom_code:
            custom_code_filenames = [f.text for f in custom_code.findall("file")]
        else:
            custom_code_filenames = []

        log_modules = get_unique_log_modules(node.find("logging") or [])

        defines = board_node.find("defines")
        if defines:
            defines = [d.text for d in defines.findall("define")]
        else:
            defines = []

        arduino_libs = board_node.find("libraries")
        if arduino_libs:
            arduino_libs = [d.text for d in arduino_libs.findall("library")]
        else:
            arduino_libs = []

        return cls(
            board_type, name, devices, parameters, modules, settings_dict, info, raat,
            custom_code_filenames, board_node.attrib, log_modules, defines, arduino_libs
        )

    @classmethod
    def from_yaml(cls, board_dict):
        board_type = board_dict["board"]["type"]
        name = board_dict["board"]["name"]
        devices = [Device.from_yaml(dev) for dev in board_dict["board"]["devices"]]

        if "settings" in board_dict["board"]:
            settings = [Setting.from_yaml(setting) for setting in board_dict["board"]["settings"]]
            settings_dict = {setting.id: setting for setting in settings}
        else:
            settings_dict = {}

        if "custom_code" in board_dict["board"]:
            filenames = board_dict["board"]["custom_code"]
        else:
            filenames = []

        if "defines" in board_dict["board"]:
            defines = board_dict["board"]["defines"]
        else:
            defines = []

        if "libraries" in board_dict["board"]:
            arduino_libs = board_dict["board"]["libraries"]
        else:
            arduino_libs = []

        info = board_dict["board"].get("info", "")
        raat = board_dict["board"].get("raat", {})

        log_modules = get_unique_log_modules(board_dict["board"].get("logging", []))

        return cls(
            board_type, name, devices, settings_dict, info, raat,
            filenames, board_dict["board"], log_modules, defines, arduino_libs
        )
