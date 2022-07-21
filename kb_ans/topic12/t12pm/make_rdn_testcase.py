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
        f.write("1\n")
        n = random.randrange(5, 10) + 1
        x = random.randrange(1, 100)
        y = random.randrange(200, 2000)
        max_h = y + 1
        f.write("{} {} {} {}\n".format(n, x, y, max_h))

        pltm = [[x-1, x+1, y-1]]

        while True:
            if (len(pltm) == n):
                break
            h = random.randrange(1, y-1)
            shpltm = filter(lambda x: x[2] == h, pltm)
            if (len(shpltm) != 0):
                continue
            x1 = random.randrange(1, 100)
            x2 = random.randrange(1, 100)
            x1, x2 = min(x1, x2), max(x1, x2)
            pltm.append([x1, x2, h])
        for p in pltm:
            f.write("{} {} {}\n".format(p[0], p[1], p[2]))


if __name__ == "__main__":
    #main(sys.argv[2], int(sys.argv[3]), float(sys.argv[4]))
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
