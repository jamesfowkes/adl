import logging


def get_module_logger():
    return logging.getLogger(__name__)


def apply_boardtype_override(new_boardtype, board):
    get_module_logger().info(
        "Overriding boardtype '{}' with '{}'".format(board.type, new_boardtype))
    board = board._replace(type=new_boardtype)
    return board


def apply_fqbn_override(new_fqbn, board):
    get_module_logger().info("Overriding fqbn '{}' with '{}'".format(
        board.attrs.get("fqbn", "default"), new_fqbn))
    new_attrs = board.attrs.copy()
    new_attrs["fqbn"] = new_fqbn
    board = board._replace(attrs=new_attrs)
    return board


OVERRIDE_FUNCTION_MAP = {
    "boardtype": apply_boardtype_override,
    "fqbn": apply_fqbn_override
}


def apply_overrides(overrides, board):

    for override in overrides:
        target, value = override.split(":", maxsplit=1)
        if target in OVERRIDE_FUNCTION_MAP:
            board = OVERRIDE_FUNCTION_MAP[target](value, board)
        else:
            get_module_logger().warn("Override target '{}' not found".format(target))

    return board
