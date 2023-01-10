import serial
import io
import time
import sys
import signal
import pandas as pd

ser = serial.Serial('/dev/ttyACM0')  # open serial port
ser.flushInput()

start_time = time.monotonic()

counter = 0

print(0, flush=True)

times = []

def signal_handler(sig, frame):
    running = False
    df = pd.DataFrame(times)
    df.to_csv('times.csv')
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

running = True

while running:
    try:
        ser_bytes = ser.readline()
        decoded_bytes = ser_bytes[0:len(ser_bytes)-2].decode("utf-8")

        if '# click' in decoded_bytes:
            start_time = time.monotonic()
            counter += 1
            times.append({'idx' : counter, 'event' : 'start', 'time' : start_time})
        else:
            if '#' not in decoded_bytes:
                end_time = time.monotonic()
                latency = (end_time - start_time) * 1000
                yalmd_latency = float(decoded_bytes) / 1000
                times.append({'idx' : counter, 'event' : 'end', 'time' : end_time})
                times.append({'idx' : counter, 'event' : 'latency', 'time' : yalmd_latency})
                #if counter > 5:
                    #print(end_time - latency, flush=True)
    except:
        print('# error')
