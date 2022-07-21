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
    case_cnt = 3
    print("file_name:{}, case_cnt:{}, block_path_ratio:{}".format(
        file_name, case_cnt, block_path_ratio))
    with open(file_name, 'w') as f:
        for _ in range(case_cnt):
            #n = random.randrange(1, 1e5)
            n = random.randrange(1, 10)
            #m = random.randrange(1, 1e5)
            m = random.randrange(1, 10)
            f.write("{}\n".format(n))
            for _ in range(n):
                f.write("{} ".format(random.randrange(1, 10)))
            f.write("\n")
            f.write("{}\n".format(m))
            for _ in range(m):
                act = random.choice([0, 1])
                x = random.randrange(1, n + 1)
                y = random.randrange(1, n + 1)
                x, y = min(x, y), max(x, y)
                f.write("{} {} {}\n".format(act, x, y))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
