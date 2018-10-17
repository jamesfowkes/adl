import subprocess
import logging
import shutil
from pathlib import Path

THIS_PATH = Path(__file__).parent

def get_module_logger():
    return logging.getLogger(__name__)

class ArduinoCLIInterface:

    def __init__(self):
        self.location = None

    def find(self):
        if self.location is None:
            self.location = shutil.which("arduino-cli") or shutil.which("arduino-cli.exe")
            get_module_logger().info("CLI Location: {}".format(self.location))

        return self.location

    def lib_is_installed(self, library):
        args = [self.location, "lib", "search", library]
        result = subprocess.run(args, stdout=subprocess.PIPE)
        expected_if_installed = 'Name: "{}"'.format(library)
        for l in result.stdout.splitlines():
            if l.decode("utf-8").strip() == expected_if_installed:
                get_module_logger().info("Library {} is installed".format(library))
                return True
        return False

    def core_is_installed(self, core):
        args = [self.location, "core", "list"]
        result = subprocess.run(args, stdout=subprocess.PIPE)
        for l in result.stdout.splitlines():
            try:
                installed, core_id, latest, name = l.decode("utf-8").split(maxsplit=3)
                if installed.strip() == core:
                    get_module_logger().info("Core {} is installed".format(core))
                    return True
            except:
                pass
            
        return False

    def install_lib(self, library):
        self.find()
        if not self.lib_is_installed(library):
            args = [self.location, "lib", "install", library]
            result = subprocess.run(args)
            get_module_logger().info("Lib Install: '{}'".format(" ".join(result.args)))

    def install_core(self, core):
        self.find()
        if not self.core_is_installed(core):
            args = [self.location, "core", "install", core]
            result = subprocess.run(args)
            get_module_logger().info("Core Install: '{}'".format(" ".join(result.args)))

    def verify(self, board, sketch_path):
        self.find()
        for library in board.required_libraries():
            self.install_lib(library)

        self.install_core(board.required_core)

        args = [self.location, "compile", "--fqbn", board.fqbn, str(sketch_path)]
        result = subprocess.run(args)
        get_module_logger().info("Verify: '{}'".format(" ".join(result.args)))

    def upload(self, board, sketch_path, port):
        self.find()
        args = [self.location, "upload", "-p", port, "--fqbn", board.fqbn, str(sketch_path)]
        result = subprocess.run(args)
        get_module_logger().info("Upload: '{}'".format(" ".join(result.args)))
