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
    alarm.timer()
    print("--------------------------------------------")
    print('新規ツイートを取得します:%d' %last_id)
    #ツイートを取得してtimelineに格納
    timeline = twitter.get_user_timeline(CK, CS, AT, AS, ID, last_id)

    # timelineから指定文字列を検索
    # 検索結果に応じてArduinoにシリアル通信
    for tweet in timeline:
        print("==お知らせ＝＝")
        print("新規Tweetが見つかりました")
        print("--Tweet内容--")
        print(tweet)
        print("--------------------------------------------")
        print("")
    for tweet in timeline:
        if "#Test" in tweet:
            print("#Testが見つかりました")
            serial_write.serial_w("test")
            break
        if "#turnLight" in tweet:
            print("#turnLightが見つかりました")
            serial_write.serial_w("do_t_L")
            break
        if "#turnOnAir" in tweet:
            print("#turnOnAirが見つかりました")
            serial_write.serial_w("do_t_on_A")
            break
        if "#turnOffAir" in tweet:
            print("#turnOffAirが見つかりました")
            serial_write.serial_w("do_t_off_A")
            break
        if "#setSleep" in tweet:
            print("#setSleepが見つかりました")
            pat='[0-9]{1,2}:[0-9]{1,2}'
            matchT = re.search(pat , tweet)
            if matchT:
                dt = datetime.strptime(matchT.group(0),'%H:%M')
                print(str(dt.hour)+":"+str(dt.minute)+" にアラームを設定します")
                twitter.tweet(CK, CS, AT, AS, ID,("@takumin_inu "+str(dt.hour)+":"+str(dt.minute)+"にアラームを設定します"))
                alarm.a_set(dt.hour,dt.minute)
            else:
                print("時刻指定のフォーマットが正しくありません。")
                twitter.tweet(CK, CS, AT, AS, ID,"@takumin_inu 時刻指定のフォーマットが正しくありません Tweet内容→『"+tweet+"』")
            break
        if "#unSetSleep" in tweet:
            print("#unSetSleepが見つかりました")
            alarm.unSet()
            break
    # 最終ツイートのIDを更新
    last_id = twitter.get_tweetID(CK, CS, AT, AS, ID)
    # timelineを初期化
    timeline.clear()