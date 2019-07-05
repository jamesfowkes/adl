from collections import namedtuple
from pathlib import Path

from raat import VALID_PROTOCOLS, VALID_LOG_LEVELS


class RAATConfig(namedtuple("RAATConfig", [
    "source_file", "buffer_size", "protocol",
    "tick_duration_ms", "delay_start_time",
    "log_buffer_size", "raat_log_level"])
):

    @property
    def source_path(self):
        return Path.resolve(Path(self.source_file).parent)


def get(board, source_file):

    protocol = board.raat.get("protocol", "simple")
    raat_log_level = board.raat.get("loglevel", "NONE")

    if protocol not in VALID_PROTOCOLS:
        raise Exception("Protocol {} not found in {}".format(
            protocol, VALID_PROTOCOLS))

    if raat_log_level not in VALID_LOG_LEVELS:
        raise Exception("Log level {} not found in {}".format(
            raat_log_level, VALID_LOG_LEVELS))

    config_dict = {
        "source_file": source_file,
        "protocol": protocol,
        "buffer_size": board.raat.get("buffer_size", 64),
        "tick_duration_ms": board.raat.get("tick_duration_ms", 10),
        "delay_start_time": board.raat.get("delay_start_time", 0),
        "log_buffer_size": board.raat.get("log_buffer_size", 64),
        "raat_log_level": raat_log_level
    }

    return RAATConfig(**config_dict)
