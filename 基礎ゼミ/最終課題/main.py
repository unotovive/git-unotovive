# -*- coding: utf-8 -*-
# import
import twitter
import serial_write
import json
import alarm
import re
from datetime import datetime
from time import sleep

CK = "WirnI4DVeZkj3spl3l094PGdd"                          # Consumer Key
CS = "hJlrTQH9MoLPpcZ5Mrunwzjb0mssbhonZm2XVUadaNmwC2V21D" # Consumer Secret
AT = "4898229974-Y3j8XU4Y4s2gJe8XxuEJFqROBj84AAWHFSMUxAw" # Access Token
AS = "s6PzquuSPkETdXt2bWar1GFAk1BW8Uvs4XWD0lyosSKNm"      # Accesss Token Secert
ID = "4898229974"                                         # ID
#タイムライン格納
timeline = []
last_id = twitter.get_tweetID(CK, CS, AT, AS, ID)
#ずっと
while True:
    sleep(10)
    alarm.timer();
    print('新規ツイートを取得します:%d' %last_id)
    #ツイートを取得してtimelineに格納
    timeline = twitter.get_user_timeline(CK, CS, AT, AS, ID, last_id)

    # timelineから指定文字列を検索
    # 検索結果に応じてArduinoにシリアル通信
    for tweet in timeline:
        print("新規Tweetが見つかりました")
        print("--------------------------------------------")
        print(tweet)
        print("--------------------------------------------")
    for tweet in timeline:
        if "#Test" in tweet:
            print("#Testが見つかりました")
            serial_write.serial_w("test")
            break
        if "#turnOnLight" in tweet:
            print("#turnOnLightが見つかりました")
            serial_write.serial_w("do_t_on_L")
            break
        if "#turnOffLight" in tweet:
            print("#turnOffLightが見つかりました")
            serial_write.serial_w("do_t_off_L")
            break
        if "#turnOnAir" in tweet:
            print("に起こしてが見つかりました")
            serial_write.serial_w("do_t_on_A")
            break
        if "#turnOffAir" in tweet:
            print("#turnOffAirが見つかりました")
            serial_write.serial_w("do_t_off_A")
            break
        if "#setSleep" in tweet:
            print("#setSleepが見つかりました")
            pat='[0-9]{1,2}:[0-9]{1,2}'
            match = re.search(pat , tweet)
            if True:
                print(match.group(0))
                dt = datetime.strptime(match.group(0),'%H:%M')
                alarm.a_set(dt.hour,dt.minute)
            else:
                print(match.group(0))
            break
        if "#unSetSleep" in tweet:
            print("#unSetSleepが見つかりました")
            alarm.unSet()
            break
    # 最終ツイートのIDを更新
    last_id = twitter.get_tweetID(CK, CS, AT, AS, ID)
    # timelineを初期化
    timeline.clear()