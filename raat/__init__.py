import logging
import shutil

from pathlib import Path

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
    (RAAT_CODE_PATH.joinpath("raat-callbacks.hpp"), "raat-callbacks.hpp"),
    (RAAT_CODE_PATH.joinpath("raat-interface.hpp"), "raat-interface.hpp"),
    (RAAT_CODE_PATH.joinpath("raat.hpp"), "raat.hpp",),
    (RAAT_CODE_PATH.joinpath("utility", "raat-util.hpp"), "raat-util.hpp"),
    (RAAT_CODE_PATH.joinpath("raat_defs.tpl"), "raat-defs.hpp"),
    (RAAT_CODE_PATH.joinpath("raat_application.tpl"), "raat-application.hpp"),
    (RAAT_CODE_PATH.joinpath("logging", "raat_logging.tpl"), "raat-logging.cpp"),
    (RAAT_CODE_PATH.joinpath("logging", "raat-logging.hpp"), "raat-logging.hpp"),
    (RAAT_CODE_PATH.joinpath("messages", "raat-messages.cpp"), "raat-messages.cpp"),
    (RAAT_CODE_PATH.joinpath("messages", "raat-messages.hpp"), "raat-messages.hpp"),
    (RAAT_CODE_PATH.joinpath("raat-nv.hpp"), "raat-nv.hpp"),
    (RAAT_CODE_PATH.joinpath("raat-serial.hpp"), "raat-serial.hpp")
]

PROTOCOLS_PATH = RAAT_CODE_PATH.joinpath("protocols")
VALID_PROTOCOLS = get_subfolders(PROTOCOLS_PATH)


def write_file(template_file, target_directory, target_file, raat_config, board):

    rendered_code = raat.template_engine.render_library(
        Path(template_file), raat_config, board)
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
        if file.suffix in [".hpp", ".cpp", ".c"]:
            write_file(file, target_directory, file.name, raat_config, board)

    copy_file(Path("devices/device.hpp"), target_directory)
    copy_file(Path("parameters/parameter.hpp"), target_directory)

    for template_file, target_file in RAAT_SOURCE_FILES:
        write_file(template_file, target_directory,
                   target_file, raat_config, board)


def write_main(directory, sketch_name, raat_config, board):
    target = directory.joinpath(sketch_name)
    get_module_logger().info("Writing sketch '%s'", target)
    write_file(RAAT_CODE_PATH.joinpath("raat-main.tpl"),
               directory, sketch_name, raat_config, board)


def write_board_support_package(target_directory, raat_config, board):
    rendered_code = raat.template_engine.render_board(
        board.template, raat_config, board)
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
