import os

class GenericBoard:
	def includes(self, path=None):
		
		all_includes = []
		for d in self.devices:
			for include in d.includes:
				inc_path = os.path.join(path, include) if path else include
				all_includes.append(inc_path)

		return set(all_includes)

	def sources(self, path=None):
		
		all_sources = []
		for d in self.devices:
			for src in d.sources:
				src_path = os.path.join(path, src) if path else src
				all_sources.append(src_path)

		return set(all_sources)

	def custom_code_paths(self, path=None):
		
		all_sources = []
		for src in self.custom_code:
			src_path = os.path.join(path, src) if path else src
			all_sources.append(src_path)

		return set(all_sources)