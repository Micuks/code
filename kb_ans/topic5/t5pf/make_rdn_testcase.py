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
        for k in range(3):
            n = random.randrange(1, 5) + 1
            p1 = random.randrange(1, 2) + 1
            p2 = random.randrange(1, 2) + 1
            n = random.randrange(1, 1000) + 1
            p1 = random.randrange(1, 30) + 1
            p2 = random.randrange(1, 30) + 1
            s = [i+1 for i in xrange(p1+p2)]
            random.shuffle(s)
            s1 = set(s[0:p1])
            s2 = set(s[p1:p1+p2])

            f.write("{} {} {}\n".format(n, p1, p2))
            for x in range(n):
                ai = random.randrange(p1+p2) + 1
                bi = random.randrange(p1+p2) + 1
                ans = "yes" if (ai in s1 and bi in s1) or (
                    ai in s2 and bi in s2) else "no"
                f.write("{} {} {}\n".format(ai, bi, ans))
        f.write("0 0 0\n")


if __name__ == "__main__":
    #main(sys.argv[2], int(sys.argv[3]), float(sys.argv[4]))
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
