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
    case_cnt = 3
    print("file_name:{}, case_cnt:{}, block_path_ratio:{}".format(
        file_name, case_cnt, block_path_ratio))
    with open(file_name, 'w') as f:
        f.write("{}\n".format(case_cnt))
        for _ in range(case_cnt):
            #n = random.randrange(1, 5e4)
            n = random.randrange(1, 10)
            f.write("{}\n".format(n))
            #ppl = [x for x in range(50)]
            ppl = [x for x in range(5)]
            f.write("{}\n".format(" ".join(
                str(x) for x in random.choices(ppl, k=n))))
            cmd = ["Add", "Sub", "Query"]

            k = 10
            for x in range(k):
                c = cmd[random.randrange(1, 4) - 1]
                if c == "Add" or c == "Sub":
                    idx = random.randrange(1, n + 1)
                    #val = random.randrange(1, 30)
                    val = random.randrange(1, 5)
                    f.write("{} {} {}\n".format(c, idx, val))
                else:
                    ub = random.randrange(1, n + 1)
                    lb = random.randrange(1, n + 1)
                    lb, ub = min(lb, ub), max(lb, ub)
                    f.write("{} {} {}\n".format(c, lb, ub))

            f.write("End\n")


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
