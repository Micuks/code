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
    case_cnt = 3
    with open(file_name, 'w') as f:
        #S = [chr(x) for x in range(ord('a'), ord('z') + 1)]
        S = [chr(x) for x in range(ord('a'), ord('c') + 1)]
        for _ in range(case_cnt):
            #n = random.randrange(1, 4000)
            n = random.randrange(2, 8)
            f.write("{}\n".format(n))
            for _ in range(n):
                #m = random.randrange(1, 200)
                m = random.randrange(1, 10)
                s = random.choices(S, k=m)
                f.write("{}\n".format("".join(s)))
        f.write("0\n")


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
