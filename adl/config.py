from collections import namedtuple

from adl import VALID_PROTOCOLS

ADLConfig = namedtuple("ADLConfig", ["buffer_size", "protocol", "tick_duration_ms"])

def get(board):
	adl_buffer_size = board.adl.get("buffer_size", 64)
	protocol = board.adl.get("protocol", "simple")
	tick_duration_ms = board.adl.get("tick_duration_ms", 10)

	if protocol not in VALID_PROTOCOLS:
		raise Exception("Protocol {} not found in {}".format(protocol, VALID_PROTOCOLS))
		
	return ADLConfig(adl_buffer_size, protocol, tick_duration_ms)
