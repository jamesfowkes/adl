from adl.types import SourceFileProvider

class GenericDevice(SourceFileProvider):

    @property
    def sanitised_name(self):
        return self.name.replace(" ", "_")

    def cname(self, static=True):
        if static:
            return "s_" + self.sanitised_name.lower()
        else:
            return self.sanitised_name.lower()

    @property
    def command_handler(self):
        return "return {name}.command_handler(command, reply);".format(name=self.cname())

    @property
    def adl_dependencies(self):
        return []

    @property
    def required_libraries(self):
        return []

    @property
    def ctype(self):
        return type(self).__name__

class GenericDevicePlugin:

    def verify_settings(self, device):
        if hasattr(self, "REQUIRED_SETTINGS"):
            for setting in self.REQUIRED_SETTINGS:
                if setting not in device.settings:
                    raise Exception("Expected setting {} in device '{}'".format(setting, device.name))
