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
        S = [chr(x + ord('a')) for x in range(ord('z') - ord('a') + 1)]
        for _ in range(case_cnt):
            n = random.randrange(1, 25)
            m = random.randrange(0, 10)
            k = random.randrange(-1, m)
            #print(S)
            #s = [str(random.randrange(0, 20) - 10) for _ in range(n)]
            #t = [str(random.randrange(0, 20) - 10) for _ in range(m)]
            f.write("{} {} {}\n".format(n, m, k))
            for x in range(m):
                l = random.randrange(1, 10)
                s = "".join(random.choices(S, k=l))
                f.write("{}\n".format(s))
        f.write("0 0 0\n")


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
