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
        S = ['A', 'T', 'G', 'C']
        for _ in range(case_cnt):
            n = random.randrange(1, 50)
            #n = random.randrange(1, 3)
            f.write("{}\n".format(n))
            for _ in range(n):
                l = random.randrange(1, 10)
                #l = random.randrange(1, 3)
                s = "".join(random.choices(S, k=l))
                f.write("{}\n".format(s))
            l = random.randrange(1, 40)
            #l = random.randrange(1, 10)
            s = "".join(random.choices(S, k=l))
            f.write("{}\n".format(s))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
