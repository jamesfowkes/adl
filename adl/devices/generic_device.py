class GenericDevice:

	def cname(self, static=True):
		sanitised_name = self.name.lower().replace(" ", "_")
		if static:
			return "s_" + sanitised_name
		else:
			return sanitised_name
