""" get_params.py

Usage:
	get_params.py <port> [<baudrate>]

"""

import docopt
import serial
import time

def get_param(ser, n):
	ser.write("/param/{:02d}/?\r\n".format(n).encode("ascii"))
	reply = ser.readline().decode("ascii")
	return reply.strip()

def get_params(ser):
	param_no = 1
	while True:
		reply = get_param(ser, param_no)
		if reply != "?":
			print("Param {} = {}".format(param_no, reply))
			print("/param/{:02d}/S{}".format(param_no, reply))
			time.sleep(0.1)
		else:
			return
		param_no += 1 

if __name__ == "__main__":
	args = docopt.docopt(__doc__)

	port = args["<port>"]
	baudrate = args["<baudrate>"] or 115200

	with serial.Serial(port, baudrate) as ser:
		get_params(ser)