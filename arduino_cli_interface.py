import subprocess

def verify(board, sketch_path):
	args = ["arduino-cli", "compile", "--fqbn", board.fqbn, str(sketch_path)]
	subprocess.run(args)

def upload(board, sketch_path, port):
	args = ["arduino-cli", "upload", "-p", port, "--fqbn", board.fqbn, str(sketch_path)]
	subprocess.run(args)
