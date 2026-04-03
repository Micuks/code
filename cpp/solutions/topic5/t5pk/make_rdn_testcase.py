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
    case_cnt = 1
    block_path_ratio = 0.5
    with open(file_name, 'w') as f:
        for _ in xrange(case_cnt):
            n = random.randrange(1, 5) + 1
            m = random.randrange(1, 10) + 1
            f.write("{} {}\n".format(n, m))
            for x in range(m):
                xi = random.randrange(0, n)
                yi = random.randrange(0, n)
                c = ('>' if random.uniform(0, 1)
                     < block_path_ratio else '<')
                if xi == yi:
                    c = '='
                f.write("{}{}{}\n".format(xi, c, yi))


if __name__ == "__main__":
    #main(sys.argv[2], int(sys.argv[3]), float(sys.argv[4]))
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
