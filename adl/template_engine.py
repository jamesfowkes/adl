import os
import jinja2
import datetime

THIS_PATH = os.path.dirname(__file__)

board_loader = jinja2.Environment(loader=jinja2.FileSystemLoader(THIS_PATH+"/boards"))
library_loader = jinja2.Environment(loader=jinja2.FileSystemLoader(THIS_PATH+"/adl_code"))

class Context:

	def __init__(self):
		self._time = datetime.datetime.now()

	def time(self, fmt):
		return fmt.format(self._time)

def render_library(template_path, adl):
	return library_loader.get_template(template_path).render(adl=adl, context=Context())

def render_board(template_name, board):	
	return board_loader.get_template(template_name).render(board=board, context=Context())
