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
        #n = random.randrange(0, 1000000) + 1
        #m = random.randrange(0, 1000)
        n = random.randrange(0, 50)
        m = random.randrange(0, 15)
        r = random.randrange(1, n)
        f.write("{} {} {}\n".format(n, m, r))

        for _ in xrange(m):
            x = random.randrange(0, n)
            y = random.randrange(0, n)
            x, y = min(x, y), max(x, y)
            while x == y:
                x = random.randrange(0, n)
                y = random.randrange(0, n)
                x, y = min(x, y), max(x, y)
            #effi = random.randrange(0, 1000000)
            effi = random.randrange(0, 50)
            f.write("{} {} {}\n".format(x, y, effi))


if __name__ == "__main__":
    #main(sys.argv[2], int(sys.argv[3]), float(sys.argv[4]))
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
