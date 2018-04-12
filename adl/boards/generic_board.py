import os

class GenericBoard:

	def adl_sources(self, full_path):
		all_deps = []
		for d in self.devices:
			for dep in d.adl_dependencies:
				for src in dep.sources:
					inc_path = os.path.join(dep.directory, src) if full_path else src
					all_deps.append(inc_path)

		return set(all_deps)

	def adl_includes(self, full_path):
		all_deps = []
		for d in self.devices:
			for dep in d.adl_dependencies:
				for header in dep.headers:
					inc_path = os.path.join(dep.directory, header) if full_path else header
					all_deps.append(inc_path)

		return set(all_deps)
		
	def includes(self, full_path):
		
		all_includes = []
		for d in self.devices:
			for include in d.includes:
				inc_path = os.path.join(d.directory, include) if full_path else include
				all_includes.append(inc_path)

		return set(all_includes)

	def sources(self, full_path):
		
		all_sources = []
		for d in self.devices:
			for src in d.sources:
				src_path = os.path.join(d.directory, src) if full_path else src
				all_sources.append(src_path)

		return set(all_sources)

	def custom_code_paths(self, path=None):
		
		all_sources = []
		for src in self.custom_code:
			src_path = os.path.join(path, src) if path else src
			all_sources.append(src_path)

		return set(all_sources)