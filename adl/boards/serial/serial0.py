class Serial0:

    def __init__(self, baudrate):
        self.baudrate = baudrate

    @property
    def setup(self):
        return "Serial.begin({});".format(self.baudrate)

    def read(self, adl_read_fn):
        return """
        void serialEvent()
        {{
            while (Serial.available())
            {{
                {}((char)Serial.read());
            }}
        }}""".format(adl_read_fn)

    def send(self, to_send):
        return "Serial.println({});".format(to_send)

    @property
    def sources(self):
        return []

    @property
    def includes(self):
        return []

    def get_sources(self, target_type):
        return [s for s in self.sources if isinstance(s, target_type)]

    def get_includes(self, target_type):
        return [s for s in self.includes if isinstance(s, target_type)]