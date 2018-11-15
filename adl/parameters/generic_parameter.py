from adl.types import SourceFileProvider

class GenericParameter(SourceFileProvider):

    def cname(self, static=True):
        sanitised_name = self.name.lower().replace(" ", "_")
        if static:
            return "s_" + sanitised_name
        else:
            return sanitised_name

    @property
    def command_handler(self):
        return "return {name}.command_handler(command, reply);".format(name=self.cname())

class GenericParamPlugin:

    def verify_settings(self, param):
        if hasattr(self, "REQUIRED_SETTINGS"):
            for setting in self.REQUIRED_SETTINGS:
                if setting not in param.settings:
                    raise Exception("Expected setting {} in param '{}'".format(setting, param.name))
