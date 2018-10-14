import subprocess
import logging
from pathlib import Path

THIS_PATH = Path(__file__).parent

def get_module_logger():
	return logging.getLogger(__name__)

def install(library):
	args = ["arduino-cli", "lib", "install", library]
	result = subprocess.run(args)
	get_module_logger().info("Install: '{}'".format(" ".join(result.args)))

def verify(board, sketch_path):
	args = ["arduino-cli", "compile", "--fqbn", board.fqbn, str(sketch_path)]
	result = subprocess.run(args)
	get_module_logger().info("Verify: '{}'".format(" ".join(result.args)))

def upload(board, sketch_path, port):
	args = ["arduino-cli", "upload", "-p", port, "--fqbn", board.fqbn, str(sketch_path)]
	result = subprocess.run(args)
	get_module_logger().info("Upload: '{}'".format(" ".join(result.args)))
