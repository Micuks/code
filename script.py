# 复制代码

import random

def luhn_residue(digits):
   return sum(sum(divmod(int(d)*(1 + i%2), 10))
                for i, d in enumerate(digits[::-1])) % 10

### 生成imei
def getImei(N):
       part = ''.join(str(random.randrange(0,9)) for _ in range(N-1))
       res = luhn_residue('{}{}'.format(part, 0))
       return '{}{}'.format(part, -res%10)

### 检测
def isimei(imei):
    try:
        imeiChar = list(imei)  # .toCharArray()
        resultInt = 0
        i = 0
        while i < len(imeiChar) - 1:
            a = int(imeiChar[i])
            i += 1
            temp = int(imeiChar[i]) * 2
            b = (temp - 9, temp)[temp < 10]  # temp if temp < 10 else temp - 9
            resultInt += a + b
            i += 1
        resultInt %= 10
        resultInt = (10 - resultInt, 0)[resultInt == 0]
        crc = int(imeiChar[14])
        return resultInt == crc
    except:
        return False

print(isimei(getImei(15)))
