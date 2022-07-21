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
        f.write("{}\n".format(case_cnt))
        for _ in range(case_cnt):
            lizard_randomness = 0.9
            n = random.randrange(1, 20)
            m = random.randrange(1, 20)
            d = random.randrange(1, 4)
            '''
            n = random.randrange(1, 5)
            m = random.randrange(1, 5)
            d = random.randrange(1, 4)
            '''
            f.write("{} {}\n".format(n, d))
            ps = [0, 0, 0, 1, 2, 3]
            pcnt = []
            for x in range(n):
                row = random.choices(ps, k=m)
                f.write("{}\n".format("".join(str(x) for x in row)))
                pcnt.append(row)
            for prow in pcnt:
                lrow = [
                    'L' if x > 0 and random.uniform(0, 1) < lizard_randomness
                    else '.' for x in prow
                ]
                f.write("{}\n".format("".join(lrow)))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
