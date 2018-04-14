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

	@property
	def adl_dependencies(self):
		return []
