import serial
from time import sleep


def serial_w(msg):
    with serial.Serial("COM3",9600) as ser:
            sleep(3)
            flag_byte = msg.encode('utf-8')

            ser.write(flag_byte)

if __name__ == "__main__":
    serial_w("hello")

