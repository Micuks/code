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
from collections import defaultdict


def main(file_name, case_cnt, block_path_ratio):
    global prime
    print("file_name:{}, case_cnt:{}, block_path_ratio:{}".format(
        file_name, case_cnt, block_path_ratio))
    case_cnt = 1
    with open(file_name, 'w') as f:
        for _ in range(case_cnt):
            #m = random.randrange(1, 2e1)
            #S = ['a', 'b', 'c']
            #s = [str(random.randrange(0, 20) - 10) for _ in range(n)]
            #t = [str(random.randrange(0, 20) - 10) for _ in range(m)]
            #s = random.choices(S, k=m)
            #f.write("{}\n".format("".join(s)))
            k = random.randrange(10, 30)
            #k = random.randrange(1, 3)
            c = random.randrange(50, 200)
            #c = random.randrange(1, 10)
            m = random.randrange(8, 15)
            #m = 13
            gm = defaultdict(lambda: defaultdict(int))
            for i in range(k + c):
                for j in range(i + 1, k + c):
                    gm[i][j] = gm[j][i] = random.randrange(1, 200)
            f.write("{} {} {}\n".format(k, c, m))
            for i in range(k + c):
                for j in range(k + c):
                    f.write("{} ".format(gm[i][j]))
                f.write("\n")


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
