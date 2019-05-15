import os
import jinja2
import datetime
import logging

from pathlib import Path, PurePosixPath

THIS_PATH = Path(__file__).parent

try:
    from git import Repo
    REPO_PATH = THIS_PATH.joinpath("..")
    repo = Repo(REPO_PATH)
    GIT_VERSION_INFO = "Branch: " + repo.active_branch.name
    GIT_VERSION_INFO += ", SHA: " + repo.head.object.hexsha[:8]
    if repo.is_dirty():
        GIT_VERSION_INFO += " (repo is dirty)"

except Exception as e:
    GIT_VERSION_INFO = "No repo information found: " + str(e)

BOARDS_PATH = THIS_PATH.joinpath("boards")
LIBRARY_PATH = THIS_PATH.joinpath("raat_code")

board_loader = jinja2.Environment(loader=jinja2.FileSystemLoader(str(BOARDS_PATH)))
library_loader = jinja2.Environment(loader=jinja2.FileSystemLoader(str(LIBRARY_PATH)))

def get_logger():
    return logging.getLogger(__name__)

class Context:

    def __init__(self):
        self._time = datetime.datetime.now()

    def time(self, fmt):
        return fmt.format(self._time)

    def raat_version(self):
        return GIT_VERSION_INFO

def jinja2_path(p):
    #jinja2 paths are NOT filesystem path! Always use forward slashes!
    return PurePosixPath(p)

def render_library(template_path, raat, board):
    try:
        target = str(jinja2_path(template_path.relative_to(LIBRARY_PATH)))
        get_logger().info("Rendering %s", target)
        return library_loader.get_template(target).render(raat=raat, board=board, context=Context())
    except jinja2.exceptions.TemplateNotFound:
        if THIS_PATH.joinpath("raat_code", template_path).exists():
            get_logger().error("Template '%s' exists but not found in jinja2 environment", template_path)
        else:
            get_logger().error("Template '%s' does not exist", template_path)
        raise
    except:
        raise

def render_board(template_path, raat, board):
    target = str(jinja2_path(template_path.relative_to(BOARDS_PATH)))    
    return board_loader.get_template(target).render(raat=raat, board=board, context=Context())
