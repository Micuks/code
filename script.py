import re

strs =[ "2022-10-21 15:11:35 吴清柳<imwql@qq.com>\n",
       "2022-10-21 15:11:44 Mr.Goddess(215381250)\n", "没用的登西\n"]
# pattern = r"^\d+-\d+-\d+\ \d+:\d+:\d+\ .*$"
pattern = r"^\d+-\d+-\d+\s\d+:\d+:\d+\s.*$"
match = [re.search(pattern, str) for str in strs]
for m, s in zip(match, strs):
    if(isinstance(m, re.Match)):
        print(m.group(0))
    else:
        print("No match in {}".format(s))
