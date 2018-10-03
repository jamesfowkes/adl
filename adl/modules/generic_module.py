class GenericModule:
	
	def get_sources(self, target_type):
		return [s for s in self.sources if isinstance(s, target_type)]

	def get_includes(self, target_type):
		return [s for s in self.includes if isinstance(s, target_type)]
