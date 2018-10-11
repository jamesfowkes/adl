import logging

def get_module_logger():
	return logging.getLogger(__name__)

def apply_boardtype_override(new_boardtype, board):
	get_module_logger().info("Overriding boardtype '{}' with '{}'".format(board.type, new_boardtype))
	board = board._replace(type=new_boardtype)
	return board

OVERRIDE_FUNCTION_MAP = {
	"boardtype": apply_boardtype_override
}

def apply_overrides(overrides, board):

	for override in overrides:
		target, value = override.split(":", maxsplit=1)
		if target in OVERRIDE_FUNCTION_MAP:
			board = OVERRIDE_FUNCTION_MAP[target](value, board)	
		else:
			get_module_logger().warn("Override target '{}' not found".format(target))

	return board
