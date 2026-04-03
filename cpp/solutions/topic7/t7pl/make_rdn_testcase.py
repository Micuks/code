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
        f.write("{}\n".format(case_cnt))
        for _ in range(case_cnt):
            n = random.randrange(2, 10)
            m = random.randrange(1, 10)
            f.write("{} {}\n".format(n, m))
            for _ in range(m):
                op = random.choice([1, 2])
                if op == 1:
                    a = random.randrange(0, n)
                    b = random.randrange(1, n)
                    f.write("{} {} {}\n".format(op, a, b))
                else:
                    a, b = random.randrange(0, n), random.randrange(0, n)
                    a, b = min(a, b), max(a, b)
                    f.write("{} {} {}\n".format(op, a, b))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
