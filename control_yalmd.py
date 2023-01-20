import serial
import io
import time
import sys
import signal
import random
from subprocess import Popen, PIPE, CalledProcessError
import threading
import numpy as np
import pandas as pd

fw_name = sys.argv[1]
num_measurements = int(sys.argv[2])
run_fw_test = bool(int(sys.argv[3]))
out_path = sys.argv[4]

measuring = True

p = None

last_fw = 0

def read_latency_tester():
    global measuring
    global p
    global last_fw

    #cmd = ['./latency_tester/bin/latency_tester', '/dev/input/event20', 'test']
    cmd = 'exec ./latency_tester/bin/latency_tester /dev/input/event20 test'
    p = Popen(cmd, stdout=PIPE, bufsize=1, universal_newlines=True, shell=True)
    for line in p.stdout:
        #print(line, end='', flush=True) # process line here
        last_fw = int(line)
        if measuring == False:
            break
    p.kill()

    #if p.returncode != 0:
    #    raise CalledProcessError(p.returncode, p.args)

read_latency_tester_thread = threading.Thread(target=read_latency_tester, daemon=True)

ser = serial.Serial('/dev/ttyACM0')  # open serial port
ser.flushInput()

def signal_handler(sig, frame):
    measuring = False
    time.sleep(1)
    print(np.mean(measurements))
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

if run_fw_test:
    read_latency_tester_thread.start()

time.sleep(1)

counter = 0
#num_measurements = 100

measurements = []

while True:
    if counter < num_measurements:
        ser.write('m'.encode())
    else:
        measuring = False
        break

    try:
        ser_bytes = ser.readline()
        decoded_bytes = ser_bytes[0:len(ser_bytes)-2].decode("utf-8")
        if measuring:
            #print(decoded_bytes, flush=True)
            #measurements.append(int(decoded_bytes))
            ete = int(decoded_bytes)
            diff = (ete - last_fw) / 1000
            measurements.append({'id' : counter, 'framework' : fw_name, 'fw_running' : run_fw_test, 'ete' : ete, 'fw' : last_fw, 'diff' : diff})
            #print(diff, flush=True)
        counter += 1
    except Exception as e:
        print(e)
        break
    #time.sleep(float(random.randint(200, 2000)) / 1000.0)

df = pd.DataFrame(measurements)
df.to_csv(out_path)

#print('end')
ser.close()
if run_fw_test:
    p.kill()
    read_latency_tester_thread.join()
#print(np.mean(measurements), np.std(measurements))
sys.exit(0)
