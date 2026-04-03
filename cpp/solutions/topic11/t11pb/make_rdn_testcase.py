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
    case_cnt = 1
    with open(file_name, 'w') as f:
        for _ in range(case_cnt):
            #n = random.randrange(1, 100)
            #fc = random.randrange(1, 100)
            #d = random.randrange(1, 100)
            n = random.randrange(1, 5)
            fc = random.randrange(1, 5)
            d = random.randrange(1, 5)
            f.write("{} {} {}\n".format(n, fc, d))
            #nlist = [x for x in range(1, n + 1)]
            for x in range(n):
                di = random.randrange(1, d + 1)
                fi = random.randrange(1, fc + 1)
                fsample = list(random.sample(range(1, fc + 1), fi))
                dsample = list(random.sample(range(1, d + 1), di))
                fsample.sort()
                dsample.sort()
                f.write("{} {} {} {}\n".format(
                    fi, di, " ".join(str(x) for x in fsample),
                    " ".join(str(x) for x in dsample)))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
