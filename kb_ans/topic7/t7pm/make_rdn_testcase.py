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
            m = random.randrange(1, 20)
            n = random.randrange(2, 20)
            S = ['DS', 'NS', 'STUDY!!']
            #s = [str(random.randrange(0, 20) - 10) for _ in range(n)]
            #t = [str(random.randrange(0, 20) - 10) for _ in range(m)]
            f.write("{} {}\n".format(n, m))
            s = random.choices(S, k=m)
            for op in s:
                if (op == 'DS'):
                    c = random.randrange(1, n)
                    f.write("{} {}\n".format(op, c))
                elif (op == 'NS'):
                    c = random.randrange(1, n)
                    f.write("{} {}\n".format(op, c))
                else:
                    c1 = random.randrange(1, n)
                    c2 = random.randrange(1, n)
                    c1, c2 = min(c1, c2), max(c1, c2)
                    f.write("{} {} {}\n".format(op, c1, c2))
            #f.write("{}\n".format("".join(s)))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
