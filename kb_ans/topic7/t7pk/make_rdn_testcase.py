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
            m = random.randrange(1, 10)
            n = random.randrange(1, 10)
            f.write("{} {}\n".format(n, m))
            ops = random.choices([1, 2, 3, 4], k=m)
            for op in ops:
                x, y = random.randrange(1, n + 1), random.randrange(1, n + 1)
                x, y = min(x, y), max(x, y)
                if op == 4:
                    p = random.choice([1, 2, 3])
                    f.write("{} {} {} {}\n".format(op, x, y, p))
                else:
                    c = random.randrange(1, 12)
                    f.write("{} {} {} {}\n".format(op, x, y, c))

            f.write("0 0\n")


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
