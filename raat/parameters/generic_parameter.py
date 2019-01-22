from raat.types import SourceFileProvider

class GenericParameter(SourceFileProvider):

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
    def ctype(self):
        return type(self).__name__
        
class GenericParamPlugin:

    def verify_settings(self, param):
        if hasattr(self, "REQUIRED_SETTINGS"):
            for setting in self.REQUIRED_SETTINGS:
                if setting not in param.settings:
                    raise Exception("Expected setting {} in param '{}'".format(setting, param.name))
