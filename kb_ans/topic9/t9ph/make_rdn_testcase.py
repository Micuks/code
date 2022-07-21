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
    #case_cnt = 1
    print("file_name:{}, case_cnt:{}, block_path_ratio:{}".format(
        file_name, case_cnt, block_path_ratio))
    with open(file_name, 'w') as f:
        f.write("{}\n".format(case_cnt))
        for _ in range(case_cnt):
            n = random.randrange(5, 10)
            m = random.randrange(5, 10)
            nl = list(range(1, n + 1))
            ml = list(range(1, m + 1))
            f.write("{} {}\n".format(n, m))
            for _ in range(n):
                k = random.randrange(1, m)
                f.write("{} ".format(k))
                match = " ".join(str(x) for x in random.sample(ml, k=k))
                f.write("{}\n".format(match))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
