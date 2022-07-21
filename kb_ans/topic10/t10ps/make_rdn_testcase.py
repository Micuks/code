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
            #n = random.randrange(2, 40)
            #m = random.randrange(2, 123)
            n = 3
            m = 5
            f.write("{} {}\n".format(n, m))
            for x in range(m):
                a = random.randrange(1, n + 1)
                b = random.randrange(1, n + 1)
                while b == a:
                    b = random.randrange(1, n + 1)
                f.write("{} {}\n".format(a, b))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
