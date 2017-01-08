from collections import namedtuple

from adl import VALID_PROTOCOLS

ADLConfig = namedtuple("ADLConfig", ["buffer_size", "protocol"])

def get(board):
	adl_buffer_size = board.adl.get("buffer_size", 32)
	protocol = board.adl.get("protocol", None)

	if protocol not in VALID_PROTOCOLS:
		raise Exception("Protocol {} not found in {}".format(protocol, VALID_PROTOCOLS))
		
	return ADLConfig(adl_buffer_size, protocol)
