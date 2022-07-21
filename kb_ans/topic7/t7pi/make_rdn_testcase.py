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
        for _ in range(case_cnt):
            n = random.randrange(1, 20)
            m = random.randrange(1, 5)
            f.write("{} {}\n".format(n, m))
            #s = random.choices(['D', 'Q', 'R'], k=m)
            s = random.choices(['D', 'Q'], k=m)
            dset = {}
            for se in s:
                if se == 'R':
                    f.write("{}\n".format(se))
                else:
                    k = random.randrange(1, n)
                    while k in dset:
                        k = random.randrange(1, n)
                    f.write("{} {}\n".format(se, k))
            f.write('\n')


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
