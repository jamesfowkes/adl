import os
import jinja2
import datetime
import logging

from pathlib import Path, PurePosixPath

THIS_PATH = Path(__file__).parent

BOARDS_PATH = THIS_PATH.joinpath("boards")
LIBRARY_PATH = THIS_PATH.joinpath("adl_code")

board_loader = jinja2.Environment(loader=jinja2.FileSystemLoader(str(BOARDS_PATH)))
library_loader = jinja2.Environment(loader=jinja2.FileSystemLoader(str(LIBRARY_PATH)))

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
		target = str(jinja2_path(template_path.relative_to(LIBRARY_PATH)))
		get_logger().info("Rendering %s", target)
		return library_loader.get_template(target).render(adl=adl, board=board, context=Context())
	except jinja2.exceptions.TemplateNotFound:
		if THIS_PATH.joinpath("adl_code", template_path).exists():
			get_logger().error("Template '%s' exists but not found in jinja2 environment", template_path)
		else:
			get_logger().error("Template '%s' does not exist", template_path)
		raise
	except:
		raise

def render_board(template_name, adl, board):	
	return board_loader.get_template(template_name).render(adl=adl, board=board, context=Context())
