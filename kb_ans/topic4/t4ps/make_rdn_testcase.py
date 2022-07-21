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
#import forzenset


def main(file_name, case_cnt, block_path_ratio):
    print("file_name:{}, case_cnt:{}, block_path_ratio:{}".format(
        file_name, case_cnt, block_path_ratio))
    with open(file_name, 'w') as f:
        pt = frozenset()
        n = random.randrange(30, 100)
        ml = random.randrange(1, 10)
        md = random.randrange(1, 10)
        f.write("{} {} {}\n".format(n, ml, md))
        i = 0
        while i < ml:
            xi, yi = random.randrange(1, n+1), random.randrange(1, n+1)
            while (frozenset([xi, yi]) in pt) and xi != yi:
                xi, yi = random.randrange(1, n+1), random.randrange(1, n+1)
                print("fuckyou")
            pt = frozenset(list(pt) + [frozenset([xi, yi])])
            val = random.randrange(1, 20)
            f.write("{} {} {}\n".format(xi, yi, val))
            i += 1
        pt = frozenset()
        i = 0
        while i < md:
            xi, yi = random.randrange(1, n+1), random.randrange(1, n+1)
            while (frozenset([xi, yi]) in pt) and xi != yi:
                xi, yi = random.randrange(1, n+1), random.randrange(1, n+1)
                print("fuckyou")
            pt = frozenset(list(pt) + [frozenset([xi, yi])])
            val = random.randrange(1, 20)
            f.write("{} {} {}\n".format(xi, yi, val))
            i += 1
        f.write("\n")


if __name__ == "__main__":
    #main(sys.argv[2], int(sys.argv[3]), float(sys.argv[4]))
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
