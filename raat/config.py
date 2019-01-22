from collections import namedtuple
from pathlib import Path

from raat import VALID_PROTOCOLS

class RAATConfig(namedtuple("RAATConfig", [
    "source_file", "buffer_size", "protocol",
    "tick_duration_ms", "delay_start_time",
    "log_buffer_size"])):

    @property
    def source_path(self):
        return Path.resolve(Path(self.source_file).parent)

def get(board, source_file):

    protocol = board.raat.get("protocol", "simple")

    if protocol not in VALID_PROTOCOLS:
        raise Exception("Protocol {} not found in {}".format(protocol, VALID_PROTOCOLS))
    
    config_dict = {
        "source_file": source_file,
        "protocol": protocol,
        "buffer_size": board.raat.get("buffer_size", 64),
        "tick_duration_ms": board.raat.get("tick_duration_ms", 10),
        "delay_start_time": board.raat.get("delay_start_time", 0),
        "log_buffer_size": board.raat.get("log_buffer_size", 64),
    }
        
    return RAATConfig(**config_dict)