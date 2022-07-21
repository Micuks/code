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
            rdlmt = 1e3
            rdlmt = 5
            n = random.randrange(1, rdlmt)
            n = 5
            xylmt = 1e6
            xylmt = 10
            zlmt = 500
            zlmt = 5
            f.write("{}\n".format(n))
            for N_ in range(n):
                x1, x2 = random.randrange(xylmt), random.randrange(xylmt)
                while x1 == x2:
                    x1, x2 = random.randrange(xylmt), random.randrange(xylmt)
                y1, y2 = random.randrange(xylmt), random.randrange(xylmt)
                while y1 == y2:
                    y1, y2 = random.randrange(xylmt), random.randrange(xylmt)
                z1, z2 = random.randrange(zlmt), random.randrange(zlmt)
                while z1 == z2:
                    z1, z2 = random.randrange(zlmt), random.randrange(zlmt)
                x1, x2 = min(x1, x2), max(x1, x2)
                y1, y2 = min(y1, y2), max(y1, y2)
                z1, z2 = min(z1, z2), max(z1, z2)
                f.write("{} {} {} {} {} {}\n".format(x1, y1, z1, x2, y2, z2))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
