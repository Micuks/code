#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2019 zhangxianwen <zhangxianwen@zhangxianwen-localhost>
#
# Distributed under terms of the MIT license.
# 2019-12-03 22:18

import os
import sys
import io
import random
import math


def left_turn(p0, p1, p2):
    p0p1 = [p1[0] - p0[0], p1[1] - p0[1]]
    p1p2 = [p2[0] - p1[0], p2[1] - p1[1]]
    return p0p1[0] * p1p2[1] - p0p1[1] * p1p2[0] > 0


def convex_hull(pts):
    p0 = min(pts)
    raw = sorted(filter(lambda x: x != p0, pts),
                 key=lambda x:
                 (x[1] - p0[1]) / math.sqrt((x[0] - p0[0]) * (x[0] - p0[0]) +
                                            (x[1] - p0[1]) * (x[1] - p0[1])))

    stck = [p0, raw[0]] + [[0, 0]] * (len(raw) - 1)
    print("p0: {} pts:{}, stck:{}\n".format(p0, len(pts), len(stck)))
    raw = raw[1:]
    scnt = 2
    print("stck[0]: {} stck[1]: {}\n".format(stck[0], stck[1]))
    for i in range(len(raw)):
        pt = raw[i]
        while scnt > 1 and left_turn(stck[scnt - 2], stck[scnt - 1],
                                     pt) == False:
            print("left_uturn {} {} {} failed scnt--:{}\n".format(
                stck[scnt - 2], stck[scnt - 1], pt, scnt))
            scnt -= 1
        stck[scnt] = pt
        scnt += 1
    return stck[0:scnt]


def main(file_name, case_cnt, block_path_ratio):
    plb = -10000
    pub = 10001
    global prime
    print("file_name:{}, case_cnt:{}, block_path_ratio:{}".format(
        file_name, case_cnt, block_path_ratio))
    case_cnt = 1
    with open(file_name, 'w') as f:
        for _ in range(case_cnt):
            n = random.randrange(3, 300)
            p = random.randrange(3, 300)
            pts = [[random.randrange(plb, pub),
                    random.randrange(plb, pub)] for _ in range(5, 300)]
            pts = convex_hull(pts)
            #random.shuffle(pts)
            n = len(pts)

            f.write("{} {}\n".format(n, p))
            for pt in pts:
                f.write("{} {}\n".format(pt[0], pt[1]))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
