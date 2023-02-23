import sys
from math import inf
from collections import deque,defaultdict
from datetime import date,timedelta
sys.stdin = open("in","rt")
#sys.stdout = open("output.txt","wt")

n,m = map(int,input().split())
p = [0] + list(map(int,input().split()))
t = [0] + list(map(int,input().split()))
A = [0] * (m + 1)
B = [0] * (m + 1)

# 无依赖 的最早开始时间
for i in range(1,m+1):
    if p[i] == 0:
        A[i] = 1 

# 有依赖 的最早开始时间
for i in range(1,m+1):
    if p[i] != 0:
        c = p[i]
        A[i] = A[c] + t[c]
f = True
for i in range(1,m+1): 
    if A[i] + t[i] - 1 > n: f = False
    print(A[i],end = " ")

# 有依赖的最晚开始时间
if f:
    print()
    hashmap = defaultdict(list)
    for i in range(1,m+1):
        if p[i]  != 0:
            x = p[i]
            hashmap[x].append(i)
    for i in range(m,0,-1):
        if hashmap[i] == []:
            B[i] = n - t[i] + 1
        else:
            temp = hashmap[i]
            ans = inf
            for ts in temp:
                ans = min(B[ts] - t[i],ans)
            B[i] = ans
    for i in range(1,m+1): print(B[i],end = " ")
