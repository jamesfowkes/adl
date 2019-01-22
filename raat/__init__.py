import logging
import shutil
import os

from pathlib import Path

from collections import namedtuple

import raat.devices
import raat.boards
import raat.parameters
import raat.modules
import raat.template_engine

THIS_PATH = Path(__file__).parent
RAAT_CODE_PATH = THIS_PATH.joinpath("raat_code")

def get_module_logger():
    return logging.getLogger(__name__)

def codepath():
    return RAAT_CODE_PATH
    
def get_subfolders(path):

    def absolute_path(d):
        return RAAT_CODE_PATH.joinpath(d)

    return [d.name for d in path.iterdir() if absolute_path(d).is_dir()]

RAAT_SOURCE_FILES = [
    (RAAT_CODE_PATH.joinpath("raat.cpp"), "raat.cpp"),
    (RAAT_CODE_PATH.joinpath("utility", "raat-util.cpp"), "raat-util.cpp"),
    (RAAT_CODE_PATH.joinpath("raat-callbacks.cpp"), "raat-callbacks.cpp"),
    (RAAT_CODE_PATH.joinpath("raat-callbacks.h"), "raat-callbacks.h"),
    (RAAT_CODE_PATH.joinpath("raat-interface.h"), "raat-interface.h"),
    (RAAT_CODE_PATH.joinpath("raat.h"), "raat.h",),
    (RAAT_CODE_PATH.joinpath("utility", "raat-util.h"), "raat-util.h"),
    (RAAT_CODE_PATH.joinpath("raat_defs.tpl"), "raat-defs.h"),
    (RAAT_CODE_PATH.joinpath("raat_application.tpl"), "raat-application.h"),
    (RAAT_CODE_PATH.joinpath("logging", "raat_logging.tpl"), "raat-logging.cpp"),
    (RAAT_CODE_PATH.joinpath("logging", "raat-logging.h"), "raat-logging.h"),
    (RAAT_CODE_PATH.joinpath("messages", "raat-messages.cpp"), "raat-messages.cpp"),
    (RAAT_CODE_PATH.joinpath("messages", "raat-messages.h"), "raat-messages.h"),
    (RAAT_CODE_PATH.joinpath("raat-nv.h"), "raat-nv.h"),
    (RAAT_CODE_PATH.joinpath("raat-serial.h"), "raat-serial.h")
]

PROTOCOLS_PATH = RAAT_CODE_PATH.joinpath("protocols")
VALID_PROTOCOLS = get_subfolders(PROTOCOLS_PATH)

def write_file(template_file, target_directory, target_file, raat_config, board):

    rendered_code = raat.template_engine.render_library(Path(template_file), raat_config, board)
    with target_directory.joinpath(target_file).open('w') as f:
        get_module_logger().info("Writing file %s to %s", target_file, f.name)
        f.write(rendered_code)

def copy_file(relative_src_path, target_directory):
    get_module_logger().info("Copying from %s", relative_src_path)
    filename = relative_src_path.name
    src_path = THIS_PATH.joinpath(relative_src_path)
    dst_path = target_directory.joinpath(filename)
    shutil.copy(str(src_path), str(dst_path))

def write_library(target_directory, raat_config, board):
    get_module_logger().info("Writing RAAT library to %s", str(target_directory))
    protocol_src_path = PROTOCOLS_PATH.joinpath(raat_config.protocol)
    get_module_logger().info("Using protocol from {}".format(protocol_src_path))

    for file in protocol_src_path.iterdir():
        if file.suffix in [".h", ".cpp", ".c"]:
            write_file(file, target_directory, file.name, raat_config, board)

    copy_file(Path("devices/device.h"), target_directory)
    copy_file(Path("parameters/parameter.h"), target_directory)

    for template_file, target_file in RAAT_SOURCE_FILES:
        write_file(template_file, target_directory, target_file, raat_config, board)

def write_main(directory, sketch_name, raat_config, board):
    target = directory.joinpath(sketch_name)
    get_module_logger().info("Writing sketch '%s'", target)
    write_file(RAAT_CODE_PATH.joinpath("raat-main.tpl"), directory, sketch_name, raat_config, board)

def write_board_support_package(target_directory, raat_config, board):
    rendered_code = raat.template_engine.render_board(board.template, raat_config, board)
    with target_directory.joinpath("raat-bsp.cpp").open('w') as f:
        get_module_logger().info("Writing file %s to %s", "raat-bsp.cpp", f.name)
        f.write(rendered_code)

def write_sources(target_directory, sources):
    for src in sources:
        copy_file(src, target_directory)

def set_log_level(level):
    logging.getLogger("parser").setLevel(level)
    raat.devices.set_log_level(level)
    raat.boards.set_log_level(level)
    raat.parameters.set_log_level(level)
