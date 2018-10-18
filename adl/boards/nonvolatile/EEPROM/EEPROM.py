class EEPROM:

    def __init__(self):
        pass

    @property
    def declarations(self):
        return ""

    @property
    def setup(self):
        return ""

    @property
    def address_type(self):
        return "uint16_t"

    def send(self, to_send):
        return "Serial.println({});".format(to_send)
