from requests_oauthlib import OAuth1Session
import json
url = "https://api.twitter.com/1.1/statuses/user_timeline.json"
def tweet(CK, CS, AT, AS, ID,msg):
    twitter = OAuth1Session(CK, CS, AT, AS)
    params = {"status": msg}
    req = twitter.post("https://api.twitter.com/1.1/statuses/update.json",params = params)
#tweetid取得
def get_tweetID(CK, CS, AT, AS, ID):
    params = {"user_id": ID, "count": 1}

    # OAuth
    twitter = OAuth1Session(CK, CS, AT, AS)
    req = twitter.get(url, params=params)

    #エラー判定
    if req.status_code == 200:
        timeline = json.loads(req.text)

        # 最新ツイートのツイートIDを返す
        for tweet in timeline:
            
            return tweet["id"]
    #なんかエラー
    else:
        print("Error: %d" % req.status_code)
#timeline取得
def get_user_timeline(CK, CS, AT, AS, ID, last_id):

    tweet_list = []
    params = {"user_id": ID, "count": 200, "since_id": last_id}

    # OAuth
    twitter = OAuth1Session(CK, CS, AT, AS)
    req = twitter.get(url, params=params)
    #エラー判定
    if req.status_code == 200:
        timeline = json.loads(req.text)
        #ツイートをリストにまとめて返す
        for tweet in timeline:
            tweet_list.append(tweet["text"])
    else:
        #なんかエラー
        print("Error: %d" % req.status_code)

    #ツイート格納用の配列を返す
    return tweet_list

#test用
if __name__ == "__main__":

    print(get_tweetID(CK, CS, AT, AS, ID))
    print(get_user_timeline(CK, CS, AT, AS, ID, last_id))
    tweet("基礎ゼミぃ！！！")