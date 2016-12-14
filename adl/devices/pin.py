from collections import namedtuple

class Pin(namedtuple("Pin", ["name", "number"])):
	__slots__ = ()
