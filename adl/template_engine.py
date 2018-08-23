import os
import jinja2
import datetime
import logging

from pathlib import Path, PurePosixPath

THIS_PATH = Path(__file__).parent

board_loader = jinja2.Environment(loader=jinja2.FileSystemLoader(str(THIS_PATH.joinpath("boards"))))
library_loader = jinja2.Environment(loader=jinja2.FileSystemLoader(str(THIS_PATH.joinpath("adl_code"))))

def get_logger():
	return logging.getLogger(__name__)

class Context:

	def __init__(self):
		self._time = datetime.datetime.now()

	def time(self, fmt):
		return fmt.format(self._time)

def jinja2_path(p):
	#jinja2 paths are NOT filesystem path! Always use forward slashes!
	return PurePosixPath(p)

def render_library(template_path, adl, board):
	try:
		return library_loader.get_template(str(jinja2_path(template_path))).render(adl=adl, board=board, context=Context())
	except jinja2.exceptions.TemplateNotFound:
		if THIS_PATH.joinpath("adl_code", template_path).exists():
			get_logger().error("Template '%s' exists but not found in jinja2 environment", template_path)
		else:
			get_logger().error("Template '%s' does not exist", template_path)
		raise
	except:
		raise

def render_board(template_name, board):	
	return board_loader.get_template(template_name).render(board=board, context=Context())
