import re

tests:list[str] =[ "2022-10-21 15:11:35 吴清柳<imwql@qq.com>\n",
       "2022-10-21 15:11:44 Mr.Goddess(215381250)\n",
       "没用的登西\n",
       "2022-10-21 15:11:35 吴清柳<imwql@qq.com>\n没用的登西\n2022-10-21 15:11:44 Mr.Goddess(215381250)\n"]
pattern:str = r"\d+-\d+-\d+\s\d+:\d+:\d+\s.+"

filename:str = "in.txt"

with open(filename, "r") as f:
    strs:list[str] = f.readlines()
    new_strs:list[str] = [re.sub(pattern, "", s) for s in strs]

outfile:str = "out.txt"
with open(outfile, "w") as f:
    f.writelines(new_strs)
#
# for i,o in zip(strs[:100], new_strs[:100]):
#     print(f"in: {i}out: {o}")
