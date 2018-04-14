import os
import jinja2
import datetime
import logging

THIS_PATH = os.path.dirname(__file__)

board_loader = jinja2.Environment(loader=jinja2.FileSystemLoader(THIS_PATH+"/boards"))
library_loader = jinja2.Environment(loader=jinja2.FileSystemLoader(THIS_PATH+"/adl_code"))

def get_logger():
	return logging.get_logger(__name__)

class Context:

	def __init__(self):
		self._time = datetime.datetime.now()

	def time(self, fmt):
		return fmt.format(self._time)

def render_library(template_path, adl, board):
	try:
		return library_loader.get_template(template_path).render(adl=adl, board=board, context=Context())
	except:
		get_logger().error("Exception processing template {}".format(template_path))
		raise

def render_board(template_name, board):	
	return board_loader.get_template(template_name).render(board=board, context=Context())
