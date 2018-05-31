from datetime import datetime
import locale
import serial_write
from time import sleep

rang = True
timerset=datetime(2018,5,31,16,35,0)
def a_set(time):
    global timer
    timer=time
    return

def timer():
     if(timerset.hour==datetime.now().hour):
         if(timerset.minute==datetime.now().minute):
            print("time is match")
            rang=False

if __name__ == "__main__":
    while rang:
        timer();
        print(timerset.minute)
        print(datetime.now().minute)
        sleep(5);
        
