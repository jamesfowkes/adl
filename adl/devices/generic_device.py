from adl.types import SourceFileProvider

class GenericDevice(SourceFileProvider):

    def cname(self, static=True):
        sanitised_name = self.name.lower().replace(" ", "_")
        if static:
            return "s_" + sanitised_name
        else:
            return sanitised_name

    @property
    def command_handler(self):
        return "return {name}.command_handler(command, reply);".format(name=self.cname())

    @property
    def adl_dependencies(self):
        return []

    @property
    def required_libraries(self):
        return []

class GenericDevicePlugin:

    def verify_settings(self, device):
        if hasattr(self, "REQUIRED_SETTINGS"):
            for setting in self.REQUIRED_SETTINGS:
                if setting not in device.settings:
                    raise Exception("Expected setting {} in device '{}'".format(setting, device.name))
