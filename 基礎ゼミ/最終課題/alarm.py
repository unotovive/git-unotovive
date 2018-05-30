from datetime import datetime
import locale
import serial_write
timer = datetime(2000,1,1,0,0,0)
def a_set(time):
    global timer
    timer=time
    return
def timer():
     if(timer==datetime.now()):
            serial_write.serial_w("hello")

if __name__ == "__main__":
    serial_w("hello")