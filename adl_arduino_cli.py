import subprocess

from pathlib import Path

WINDOWS_PATH = Path("C:\\Program Files (x86)\\Arduino\\arduino.exe")

def find_arduino_executable():
    if WINDOWS_PATH.exists():
        return str(WINDOWS_PATH)

    #TODO: use which to find linux path
    return "/opt/bin/arduino-1.8.5/arduino"

def get_cmd_args(arduino_executable, sketch_path):
    return [arduino_executable, "--board", "arduino:avr:uno", "--verify", sketch_path]

def build(board, sketchbook_path):
    sketch_path = board.sketch_path()
    sketch_path = sketchbook_path.joinpath(sketch_path)

    try:
        args = get_cmd_args(find_arduino_executable(), str(sketch_path))
        res = subprocess.run(args, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if len(res.stderr):
            print(res.stderr.decode("utf-8"))
    except subprocess.CalledProcessError as e:
        print("Out: " + e.output.decode("utf-8"))
        print("Std: " + e.stdout.decode("utf-8"))
        print("Err: " + e.stderr.decode("utf-8"))
        sys.exit(1)
    except:
        print("Attempted command: '{}'".format(" ".join(args)))
        raise