import serial
import time
arduino = serial.Serial('/dev/cu.usbmodem14201', 9600,timeout=1)
while True:
    arduino.write(str(-3))
    print(arduino.readline())
    time.sleep(2)


