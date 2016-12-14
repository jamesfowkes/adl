from collections import namedtuple

ADLConfig = namedtuple("ADLConfig", ["buffer_size"])

def get(board):
	adl_buffer_size = 32
	if board.adl:
		adl_buffer_size = board.adl.get("buffer_size", 32)
	return ADLConfig(adl_buffer_size)