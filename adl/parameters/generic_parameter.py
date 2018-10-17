class GenericParameter:

    def cname(self, static=True):
        sanitised_name = self.name.lower().replace(" ", "_")
        if static:
            return "s_" + sanitised_name
        else:
            return sanitised_name

    @property
    def command_handler(self):
        return "return {name}.command_handler(command, reply);".format(name=self.cname())

    def get_sources(self, target_type):
        return [s for s in self.sources if isinstance(s, target_type)]

    def get_includes(self, target_type):
        return [s for s in self.includes if isinstance(s, target_type)]
