#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2020 zhangxianwen <zhangxianwen@LAPTOP-9POC3RUN>
#
# Distributed under terms of the MIT license.
"""

"""

#import pdb
#pdb.set_trace()

import math
from itertools import *

dcnt = 365
xcnt = 1000
max_idx = 0
max_val = 364

res = [[1.0] + [0 for x in range(dcnt - 1)]]


def pii(p):
    ret = 1.0
    while p >= 0:
        ret = ret * (dcnt - p) / 365.0
        p -= 1
    return ret


def comb(n, r):
    ret = 1
    if 2 * r > n:
        r = n - r
    while r >= 0:
        ret = ret * ()

    return ret


def perm(n, r):
    div = 1
    quo = 1
    while r > 0:
        div = div * r
        quo = quo * (n - r + 1)
        r = r - 1
    return quo / div


print("pii(1):", pii(1))

for i in range(1, xcnt):
    dupper = min(i + 1, dcnt)
    #print("dupper", dupper, "i", i)
    newrow = [0.0 for x in range(dupper)]
    newrow[0] = res[i - 1][0] / 365.0
    newrow[len(newrow) - 1] = pii(dupper - 1)
    assert (i == len(res))
    for j in range(1, dupper - 1):
        newrow[j] = res[i - 1][j] * (j + 1) / 365.0 + res[i - 1][j - 1] * (
            dcnt - j) / 365.0
    res.append(newrow)
    #print("nr: {}".format(",".join(str(x) for x in newrow)))
    assert (abs(sum(newrow) - 1) < 1e-9)

    newfact = [(i + 1) * (dcnt - x - 1) for x in range(len(newrow))]
    perms = [perm(dcnt, x + 1) for x in range(len(newrow))]
    new_val = sum(map(lambda x, y, z: x * y * z, newfact, newrow, perms))
    new_val = sum(map(lambda x, y: x * y, newfact, newrow))
    print("{}-th run, acc:{}, len(nr):{}, new_val:{}".format(
        i, sum(newrow), len(newrow), new_val))
    #new_val = sum(newrow)
    if (new_val > max_val):
        max_val = new_val
        max_idx = i + 1

print("get max chance of {} at {}-th day".format(max_val, max_idx))
