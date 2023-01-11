import serial
import io
import time
import sys
import signal
import random

ser = serial.Serial('/dev/ttyACM0')  # open serial port
ser.flushInput()

def signal_handler(sig, frame):
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

time.sleep(1)

ser.write('c'.encode())

ser_bytes = ser.readline()
decoded_bytes = ser_bytes[0:len(ser_bytes)-2].decode("utf-8")
print(decoded_bytes)

while True:
    ser.write('m'.encode())
    try:
        ser_bytes = ser.readline()
        decoded_bytes = ser_bytes[0:len(ser_bytes)-2].decode("utf-8")
        print(decoded_bytes)
    except:
        print('error')
        break
    #time.sleep(float(random.randint(200, 2000)) / 1000.0)
