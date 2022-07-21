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
            n = random.randrange(1, 10)
            v = 1
            x = 5
            f.write("{} {} {}\n".format(n, v, x))
            xiub = 1e2
            biub = 1e2
            for _ in range(n):
                xi = random.randrange(0, xiub)
                while xi == x:
                    xi = random.randrange(0, xiub)
                bi = random.randrange(0, biub)
                f.write("{} {}\n".format(xi, bi))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
