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

from cyaron import *


def main(file_name, case_cnt, block_path_ratio):
    global prime
    print("file_name:{}, case_cnt:{}, block_path_ratio:{}".format(
        file_name, case_cnt, block_path_ratio))
    #case_cnt = 1
    with open(file_name, 'w') as f:
        for _ in range(case_cnt):
            p = random.randrange(1, 11)
            n = random.randrange(1, 51)
            f.write("{} {}\n".format(p, n))
            for x in range(n):
                qi = random.randrange(1, 10000)
                f.write("{} ".format(qi))
                Si = [0, 1, 2]
                So = [0, 1]
                si = random.choices(Si, k=p)
                di = random.choices(So, k=p)
                f.write("{} {}\n".format(" ".join(str(x) for x in si),
                                         " ".join(str(x) for x in di)))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
