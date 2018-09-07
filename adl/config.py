from collections import namedtuple
from pathlib import Path

from adl import VALID_PROTOCOLS

ADLConfig = namedtuple("ADLConfig", ["buffer_size", "protocol", "tick_duration_ms", "delay_start_time"])

def get(board):
	adl_buffer_size = board.adl.get("buffer_size", 64)
	protocol = board.adl.get("protocol", "simple")
	tick_duration_ms = board.adl.get("tick_duration_ms", 10)
	delay_start_time = board.adl.get("delay_start_time", 0)

	if protocol not in VALID_PROTOCOLS:
		raise Exception("Protocol {} not found in {}".format(protocol, VALID_PROTOCOLS))
		
	return ADLConfig(adl_buffer_size, protocol, tick_duration_ms, delay_start_time)
