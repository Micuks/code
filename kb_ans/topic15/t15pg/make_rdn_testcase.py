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
        for _ in range(case_cnt):
            m = random.randrange(1, 1e9)
            f.write("{}\n".format(m))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
