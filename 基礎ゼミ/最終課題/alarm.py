from datetime import datetime, date, timedelta
import locale
import serial_write
from time import sleep
#セットされているか
tSet=False
timerset=datetime(2000,1,1,0,0,0,0)

def a_set(hour,minute):
    global timerset 
    global tSet
    tSet=True
    timerset=datetime(2018,6,1,11,8,0)
    now=datetime.now()
    timerset=datetime(now.year,now.month,now.day,hour,minute,0,0)
    if(now.hour>=hour):
        if(now.minute>minute):
            tom=now.day+1
            timerset=datetime(now.year,now.month,tom,hour,minute,0)
    print(timerset)
    serial_write.serial_w("do_t_L")
    sleep(3);
    serial_write.serial_w("cc_S")

def unSet():
    global tSet
    tSet=False
    serial_write.serial_w("cc_N")

def timer():
    global tSet
    if tSet:
        now = datetime.now() 
        if(now>=timerset):
            print("==お知らせ==")
            print("--指定の時刻になりました--")
            print("")
            serial_write.serial_w("do_t_L")
            sleep(3)
            serial_write.serial_w("do_t_L")
            sleep(3)
            serial_write.serial_w("do_rang")
            tSet=False

if __name__ == "__main__":
    a_set(14,28)
    while True:
        timer()
        print(datetime.now())
        print(timerset)
        sleep(8)
        
