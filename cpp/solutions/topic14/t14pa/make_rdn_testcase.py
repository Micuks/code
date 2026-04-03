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
    with open(file_name, 'w') as f:
        f.write("1\n")
        n = random.randrange(1, 10**4)
        f.write("{}\n".format(n))

        #f.write("{} {} ".format(m, n))
        for x in range(n):
            m = random.randrange(1, 10**6) + 1
            #ai = random.randrange(0, 2**16) - 2**15
            #f.write("{} ".format(ai))
            f.write("{} ".format(m))
        f.write("\n")


if __name__ == "__main__":
    #main(sys.argv[2], int(sys.argv[3]), float(sys.argv[4]))
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
