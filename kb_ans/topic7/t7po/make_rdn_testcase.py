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
            nul = 1e3
            n = random.randrange(1, nul)
            f.write("{}\n".format(n))
            for _x in range(n):
                #x1, x2 = random.randrange(0, 1e5), random.randrange(0, 1e5)
                #y1, y2 = random.randrange(0, 1e5), random.randrange(0, 1e5)
                ul = 1e5
                x1, x2 = random.randrange(0, ul), random.randrange(0, ul)
                while x1 == x2:
                    x1, x2 = random.randrange(0, ul), random.randrange(0, ul)
                y1, y2 = random.randrange(0, ul), random.randrange(0, ul)
                while y1 == y2:
                    y1, y2 = random.randrange(0, ul), random.randrange(0, ul)
                x1, x2 = min(x1, x2), max(x1, x2)
                y1, y2 = min(y1, y2), max(y1, y2)
                f.write("{} {} {} {}\n".format(x1, y1, x2, y2))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
