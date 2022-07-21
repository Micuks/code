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
    with open(file_name, 'w') as f:
        m = random.randrange(0, 10)
        n = random.randrange(1, 2000000000)
        f.write("{} {}\n".format(m, n))
        S = ['A', 'T', 'G', 'C']
        #s = [str(random.randrange(0, 20) - 10) for _ in range(n)]
        #t = [str(random.randrange(0, 20) - 10) for _ in range(m)]
        for x in range(m):
            tlen = random.randrange(1, 10)
            s = random.choices(S, k=tlen)
            f.write("{}\n".format("".join(s)))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
