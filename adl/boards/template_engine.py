import os
import jinja2
import datetime

THIS_PATH = os.path.dirname(__file__)

fs_loader = jinja2.Environment(loader=jinja2.FileSystemLoader(THIS_PATH))

class Context:

	def __init__(self):
		self._time = datetime.datetime.now()

	def time(self, fmt):
		return fmt.format(self._time)

def render(template_name, board):
	
	return fs_loader.get_template(template_name).render(board=board, context=Context())
