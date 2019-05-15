from collections import namedtuple

TypeSpec = namedtuple("TypeSpec", ["name", "is_signed", "min", "max", "bits"])

TYPES = {
    "uint8_t" : TypeSpec("uint8_t", False, "0", "UINT8_MAX", 8),
    "int8_t" : TypeSpec("int8_t", True, "INT8_MIN", "INT8_MAX", 8),
    "uint16_t" : TypeSpec("uint16_t", False, "0", "UINT16_MAX", 16),
    "int16_t" : TypeSpec("int16_t", True, "INT16_MIN", "INT16_MAX", 16),
    "uint32_t" : TypeSpec("uint32_t", False, "0", "UINT32_MAX", 32),
    "int32_t" : TypeSpec("int32_t", True, "INT32_MIN", "INT32_MAX", 32)
}

def get(_type):
    return TYPES[_type]

def is_valid(_type):
    return _type in TYPES

