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
    print("file_name:{}, case_cnt:{}, block_path_ratio:{}".format(
        file_name, case_cnt, block_path_ratio))
    with open(file_name, 'w') as f:
        n = random.randrange(1, 100)
        m = random.randrange(1, 100)
        f.write("{} {}\n".format(m, n))
        for i in range(n):
            val = random.randrange(1, 1000)
            level = random.randrange(0, m)
            sub_cnt = random.randrange(0, n)
            f.write("{} {} {}\n".format(val, level, sub_cnt))
            for j in range(sub_cnt):
                sub_idx = random.randrange(n)
                while sub_idx == i:
                    sub_idx = random.randrange(n)
                val = random.randrange(1, 1000)
                f.write("{} {}\n".format(sub_idx+1, val))


if __name__ == "__main__":
    #main(sys.argv[2], int(sys.argv[3]), float(sys.argv[4]))
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
