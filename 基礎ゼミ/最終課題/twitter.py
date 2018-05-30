from requests_oauthlib import OAuth1Session
import json
url = "https://api.twitter.com/1.1/statuses/user_timeline.json"
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

    CK = "WirnI4DVeZkj3spl3l094PGdd"                          # Consumer Key
    CS = "hJlrTQH9MoLPpcZ5Mrunwzjb0mssbhonZm2XVUadaNmwC2V21D" # Consumer Secret
    AT = "4898229974-Y3j8XU4Y4s2gJe8XxuEJFqROBj84AAWHFSMUxAw" # Access Token
    AS = "s6PzquuSPkETdXt2bWar1GFAk1BW8Uvs4XWD0lyosSKNm"      # Accesss Token Secert
    ID = "4898229974"                                         # ID
    last_id ="1001336067411226630"
    print(get_tweetID(CK, CS, AT, AS, ID))
    print(get_user_timeline(CK, CS, AT, AS, ID, last_id))