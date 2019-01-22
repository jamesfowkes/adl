from collections import namedtuple

class TLC5973Driver(namedtuple("TLC5973Driver",["device_number"])):

    @property
    def device_string(self):
        return "D{:02d}".format(self.device_number)

    def get_command(self, r, g, b, led_start, led_end=None):

        if led_end is not None:
            return "{}{}:{},{},{},{}".format(self.device_string, led_start, led_end, r, g, b)
        else:
            return "{}{},{},{},{}".format(self.device_string, led_start, r, g, b)

    def send_command(self, stream, r, g, b, led_start, led_end=None):
        cmd = self.get_command(r, g, b, led_start, led_end) + "\n"
        stream.write(cmd.encode("utf-8"))
        return (cmd.strip(), stream.reraatine())

DELTA=8

def doR(driver, p):
    for r in range(0, 256, DELTA):
        time.sleep(0.1)
        cmd, result = driver.send_command(p, 0, r, r, 0)
        print("Sent {}, got {}".format(cmd, result))

    for r in range(256, 0, -DELTA):
        time.sleep(0.1)
        cmd, result = driver.send_command(p, 0, r, r, 0)
        print("Sent {}, got {}".format(cmd, result))

def doG(driver, p):
    for g in range(0, 256, DELTA):
        time.sleep(0.1)
        cmd, result = driver.send_command(p, g, 0, g, 0)
        print("Sent {}, got {}".format(cmd, result))

    for g in range(256, 0, -DELTA):
        time.sleep(0.1)
        cmd, result = driver.send_command(p, g, 0, g, 0)
        print("Sent {}, got {}".format(cmd, result))

def doB(driver, p):
    for b in range(0, 256, DELTA):
        time.sleep(0.1)
        cmd, result = driver.send_command(p, b, b, 0, 0)
        print("Sent {}, got {}".format(cmd, result))

    for g in range(256, 0, -DELTA):
        time.sleep(0.1)
        cmd, result = driver.send_command(p, b, b, 0, 0)
        print("Sent {}, got {}".format(cmd, result))

if __name__ == "__main__":

    import serial
    import sys
    import time
    import random
    port = sys.argv[1]
    device_number = int(sys.argv[2])
    n_leds = int(sys.argv[3])

    driver = TLC5973Driver(device_number)

    with serial.Serial(port, 115200, timeout=0.5) as p:
        time.sleep(1)
        while True:
            doR(driver, p)
            doB(driver, p)
            doG(driver, p)
            