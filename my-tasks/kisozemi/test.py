import re
tweet='aa99:99#setSleep'
if "#setSleep" in tweet:
    print("#setSleepが見つかりました")
    pat='[0-9]{1,2}:[0-9]{1,2}'
    match = re.search(pat , tweet)
    print(match.group(0))
    #dt = datetime.strptime(match.group,'%H:%M')
    #alarm.a_set(dt.hour,dt.minute)