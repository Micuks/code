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


def main(file_name, case_cnt, block_path_ratio):
    global prime
    print("file_name:{}, case_cnt:{}, block_path_ratio:{}".format(
        file_name, case_cnt, block_path_ratio))
    #case_cnt = 1
    with open(file_name, 'w') as f:
        f.write("{}\n".format(case_cnt))
        for _ in range(case_cnt):
            n = random.randrange(2, 201)
            n = 199
            #n = random.randrange(2, 5)
            m = max(n + 1, random.randrange(1, 3e4 + 1))
            m = 29999
            #m = random.randrange(10, 12)
            f.write("{} {}\n".format(n, m))
            rlist = [x for x in range(1, n + 1)]
            #rlist = random.shuffle([x for x in range(1, m + 1)])
            random.shuffle(rlist)
            rlist.append(rlist[0])
            for x in range(len(rlist) - 1):
                w = random.randrange(1, 1e4)
                f.write("{} {} {}\n".format(rlist[x], rlist[x + 1], w))
            dt = m - (len(rlist) - 1)
            for x in range(dt):
                u = random.randrange(1, n + 1)
                v = random.randrange(1, n + 1)
                w = random.randrange(1, 1e4)
                f.write("{} {} {}\n".format(u, v, w))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
