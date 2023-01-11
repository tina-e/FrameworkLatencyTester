import serial
import time

ser = serial.Serial('/dev/ttyACM0')  # open serial port
ser.flushInput()

time.sleep(1)

ser.write('c'.encode())

ser_bytes = ser.readline()
decoded_bytes = ser_bytes[0:len(ser_bytes)-2].decode("utf-8")
print(decoded_bytes)
