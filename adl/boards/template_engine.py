import os
import jinja2

THIS_PATH = os.path.dirname(__file__)

fs_loader = jinja2.Environment(loader=jinja2.FileSystemLoader(THIS_PATH))

def render(template_name, board):
	return fs_loader.get_template(template_name).render(board=board)
