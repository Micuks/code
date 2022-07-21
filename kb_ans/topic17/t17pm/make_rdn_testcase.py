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
    case_cnt = 3
    print("file_name:{}, case_cnt:{}, block_path_ratio:{}".format(
        file_name, case_cnt, block_path_ratio))
    with open(file_name, 'w') as f:
        for _ in range(case_cnt):
            S = ["0", "1"]
            #n = random.randrange(2, 11)
            n = random.randrange(2, 11)
            #m = random.randrange(1, 1e3)
            m = random.randrange(1, 10)
            f.write("{} {}\n".format(n, m))
            #s = [str(random.randrange(0, 20) - 10) for _ in range(n)]
            #t = [str(random.randrange(0, 20) - 10) for _ in range(m)]
            sn = set()
            for _ in range(n):
                #l = random.randrange(1, 10)
                l = random.randrange(1, 5)
                s = "".join(random.choices(S, k=l))
                sn.add(s)
                f.write("{}\n".format(s))

            sm = set()
            #for _ in range(m):
            while (len(sm) < m):
                #l = random.randrange(1, 50)
                l = random.randrange(1, 5)
                s = "".join(random.choices(S, k=l))
                exist = False
                for x in sn:
                    if x.find(s) != -1:
                        exist = True
                if exist:
                    continue
                sm.add(s)
                sm = sm - sn
                #f.write("{}\n".format(s))
            for x in sm:
                f.write("{}\n".format(x))

        f.write("0 0\n")


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
