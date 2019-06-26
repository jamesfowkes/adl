""" ENC28J60Handler.py

Usage:
    ENC28J60Handler.py <port> <device_number> [--baud=<baud>] [--ip=<ip>] [--mac=<mac>] [--gateway=<gateway>]

"""

import serial
import docopt
import random

def read_until_condition(ser, condition, printer=None):
    while True:
        l = ser.readline()
        if (printer):
            printer(l)
        if condition(l):
            break;

def line_printer(l):
    if len(l) > 0:
        print(l.decode("utf-8").strip())

def random_mac():
    return "{:02X}:{:02X}:{:02X}:{:02X}:{:02X}:{:02X}".format(
        random.randint(0, 255),
        random.randint(0, 255),
        random.randint(0, 255),
        random.randint(0, 255),
        random.randint(0, 255),
        random.randint(0, 255)
    )

def write_command(ser, cmd):
    ser.write((cmd + "\r\n").encode("utf-8"))
    read_until_condition(ser, lambda l: len(l) > 0, line_printer)

if __name__ == "__main__":

    args = docopt.docopt(__doc__)

    baudrate = args["--baud"] or 115200
    device_number = int(args["<device_number>"])

    with serial.Serial(port=args["<port>"], baudrate=baudrate, timeout=1) as ser:
        read_until_condition(ser, lambda l: len(l) > 0, line_printer)
        read_until_condition(ser, lambda l: len(l) == 0, line_printer)

        if args["--ip"] is not None:
            cmd = "/device/{:02d}/SIP{}".format(device_number, args["--ip"])
            print(cmd)
            write_command(ser, cmd)

        if args["--mac"] is not None:
            if args["--mac"] == "?":
                args["--mac"] = random_mac()

            cmd = "/device/{:02d}/SMAC{}".format(device_number, args["--mac"])
            print(cmd)
            write_command(ser, cmd)

        if args["--gateway"] is not None:
            cmd = "/device/{:02d}/SGWAY{}".format(device_number, args["--gateway"])
            print(cmd)
            write_command(ser, cmd)
            