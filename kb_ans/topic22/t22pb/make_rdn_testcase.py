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
        f.write("{}\n".format(case_cnt))
        clist = [x for x in range(1, 100)]
        clist = [x for x in range(1, 5)]
        for _ in range(case_cnt):
            n = random.randrange(1, 100)
            n = random.randrange(1, 10)
            f.write("{}\n".format(n))
            f.write("{}\n".format(" ".join(
                str(x) for x in random.choices(clist, k=n))))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
