import serial
import time
from pynput.keyboard import Key, Controller

keyboard = Controller()

arduino = serial.Serial('/dev/cu.usbmodem14101', 9600)
time.sleep = 1  #pause 1 seconds for python to connect with arduino

while 1:
    incoming = str(
        arduino.readline())  #read the serial data and print it as line
    print(incoming)

    if 'right' in incoming:
        for i in range(4):
            keyboard.press(Key.right)    #the press function will keep pressing the key for a short while
            keyboard.release(Key.right)  #So release the key once its pressed

    if 'left' in incoming:
        for i in range(4):
            keyboard.press(Key.left)
            keyboard.release(Key.left)
    incoming = " "  #refresh the incoming data
