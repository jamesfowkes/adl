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
        args = [self.location, "lib", "list"]
        result = subprocess.run(args, stdout=subprocess.PIPE)
        for l in result.stdout.splitlines():
            if l.decode("utf-8").strip().startswith(library):
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
            try:
                result = subprocess.run(args)
                get_module_logger().info("Lib Install Success: '{}'".format(" ".join(result.args)))
            except:
                get_module_logger().info("Lib Install Failed: '{}'".format(" ".join(result.args)))
                raise

    def install_core(self, core):
        self.find()
        if not self.core_is_installed(core):
            args = [self.location, "core", "install", core]
            try:
                result = subprocess.run(args)
                get_module_logger().info("Core Install Success: '{}'".format(" ".join(result.args)))
            except:
                get_module_logger().info("Core Install Failed: '{}'".format(" ".join(args)))
                raise

    def verify(self, board, sketch_path):
        success = False

        self.find()
        for library in board.required_libraries():
            self.install_lib(library)

        self.install_core(board.required_core)

        args = [self.location, "compile", "--fqbn", board.fqbn, str(sketch_path)]
        try:
            result = subprocess.run(args)
            success = result.returncode == 0
            if success:
                get_module_logger().info("Verify Success: '{}'".format(" ".join(result.args)))
            else:
                get_module_logger().info("Verify Failed: '{}'".format(" ".join(args)))    
        except:
            get_module_logger().info("Verify Command Exception: '{}'".format(" ".join(args)))
            raise

        return success

    def upload(self, board, sketch_path, port):
        self.find()
        args = [self.location, "upload", "-p", port, "--fqbn", board.fqbn, str(sketch_path)]
        try:
            result = subprocess.run(args)
            get_module_logger().info("Upload Success: '{}'".format(" ".join(result.args)))
        except:
            get_module_logger().info("Upload Failed: '{}'".format(" ".join(args)))
            raise
