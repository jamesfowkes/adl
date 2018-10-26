import logging
import shutil
import os

from pathlib import Path

from collections import namedtuple

import adl.devices
import adl.boards
import adl.parameters
import adl.modules
import adl.template_engine

THIS_PATH = Path(__file__).parent
ADL_CODE_PATH = THIS_PATH.joinpath("adl_code")

def get_module_logger():
    return logging.getLogger(__name__)

def codepath():
    return ADL_CODE_PATH
    
def get_subfolders(path):

    def absolute_path(d):
        return ADL_CODE_PATH.joinpath(d)

    return [d.name for d in path.iterdir() if absolute_path(d).is_dir()]

ADL_SOURCE_FILES = [
    (ADL_CODE_PATH.joinpath("adl.cpp"), "adl.cpp"),
    (ADL_CODE_PATH.joinpath("adl-util.cpp"), "adl-util.cpp"),
    (ADL_CODE_PATH.joinpath("adl-callbacks.cpp"), "adl-callbacks.cpp"),
    (ADL_CODE_PATH.joinpath("adl-callbacks.h"), "adl-callbacks.h"),
    (ADL_CODE_PATH.joinpath("adl-interface.h"), "adl-interface.h"),
    (ADL_CODE_PATH.joinpath("adl.h"), "adl.h",),
    (ADL_CODE_PATH.joinpath("adl-util.h"), "adl-util.h"),
    (ADL_CODE_PATH.joinpath("adl_defs.tpl"), "adl-defs.h"),
    (ADL_CODE_PATH.joinpath("logging", "adl_logging.tpl"), "adl-logging.cpp"),
    (ADL_CODE_PATH.joinpath("logging", "adl-logging.h"), "adl-logging.h"),
    (ADL_CODE_PATH.joinpath("messages", "adl-messages.cpp"), "adl-messages.cpp"),
    (ADL_CODE_PATH.joinpath("messages", "adl-messages.h"), "adl-messages.h"),
    (ADL_CODE_PATH.joinpath("adl-nv.h"), "adl-nv.h")
]

PROTOCOLS_PATH = ADL_CODE_PATH.joinpath("protocols")
VALID_PROTOCOLS = get_subfolders(PROTOCOLS_PATH)

def write_file(template_file, target_directory, target_file, adl_config, board):

    rendered_code = adl.template_engine.render_library(Path(template_file), adl_config, board)
    with target_directory.joinpath(target_file).open('w') as f:
        get_module_logger().info("Writing file %s to %s", target_file, f.name)
        f.write(rendered_code)

def copy_file(relative_src_path, target_directory):
    get_module_logger().info("Copying from %s", relative_src_path)
    filename = relative_src_path.name
    src_path = THIS_PATH.joinpath(relative_src_path)
    dst_path = target_directory.joinpath(filename)
    shutil.copy(str(src_path), str(dst_path))

def write_library(target_directory, adl_config, board):
    get_module_logger().info("Writing ADL library to %s", str(target_directory))
    protocol_src_path = PROTOCOLS_PATH.joinpath(adl_config.protocol)
    get_module_logger().info("Using protocol from {}".format(protocol_src_path))

    for file in protocol_src_path.iterdir():
        if file.suffix in [".h", ".cpp", ".c"]:
            write_file(file, target_directory, file.name, adl_config, board)

    copy_file(Path("devices/device.h"), target_directory)
    copy_file(Path("parameters/parameter.h"), target_directory)

    for template_file, target_file in ADL_SOURCE_FILES:
        write_file(template_file, target_directory, target_file, adl_config, board)

def write_main(directory, sketch_name, adl_config, board):
    target = directory.joinpath(sketch_name)
    get_module_logger().info("Writing sketch '%s'", target)
    write_file(ADL_CODE_PATH.joinpath("adl-main.tpl"), directory, sketch_name, adl_config, board)

def write_board_support_package(target_directory, adl_config, board):
    rendered_code = adl.template_engine.render_board(board.template, adl_config, board)
    with target_directory.joinpath("adl-bsp.cpp").open('w') as f:
        get_module_logger().info("Writing file %s to %s", "adl-bsp.cpp", f.name)
        f.write(rendered_code)

def write_sources(target_directory, sources):
    for src in sources:
        copy_file(src, target_directory)

def set_log_level(level):
    logging.getLogger("parser").setLevel(level)
    adl.devices.set_log_level(level)
    adl.boards.set_log_level(level)
    adl.parameters.set_log_level(level)
