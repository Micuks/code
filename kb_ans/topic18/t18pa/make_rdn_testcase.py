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
        #f.write("{}\n".format(case_cnt))
        for _ in range(case_cnt):
            #m = random.randrange(1, 2e1)
            #S = ['a', 'b', 'c']
            #s = [str(random.randrange(0, 20) - 10) for _ in range(n)]
            #t = [str(random.randrange(0, 20) - 10) for _ in range(m)]
            #s = random.choices(S, k=m)
            #f.write("{}\n".format("".join(s)))
            n = 20000
            f.write("{}\n".format(n))
            idx = 0
            for _ in range(n):
                key = random.randrange(1, 89)
                f.write("{} ".format(key))
                idx += 1
                if (idx % 10) == 0:
                    f.write("\n")
        f.write("{}\n".format(0))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
