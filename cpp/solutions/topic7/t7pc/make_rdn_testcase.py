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
    case_cnt = 1
    print("file_name:{}, case_cnt:{}, block_path_ratio:{}".format(
        file_name, case_cnt, block_path_ratio))
    with open(file_name, 'w') as f:
        for _ in range(case_cnt):
            n = random.randrange(3, 10)
            q = random.randrange(1, 10)
            f.write("{} {}\n".format(n, q))
            for _ in range(n):
                #f.write("{} ".format(random.randrange(1, 1e3)))
                f.write("{} ".format(random.randrange(1, 10)))
            f.write("\n")
            t = ['C', 'Q']
            for _ in range(q):
                tt = random.choice(t)
                ul = random.randrange(1, n)
                ll = random.randrange(1, n)
                ll, ul = min(ll, ul), max(ll, ul)
                if tt == 'C':
                    #addon = random.randrange(1, 1e3)
                    addon = random.randrange(1, 10)
                    f.write("{} {} {} {}\n".format(tt, ll, ul, addon))
                else:
                    f.write("{} {} {}\n".format(tt, ll, ul))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
