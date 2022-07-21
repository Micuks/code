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
        n = random.randrange(1, 100001)
        k = random.randrange(1, 100001)
        f.write('{} {}'.format(n, k))


if __name__ == "__main__":
    #main(sys.argv[2], int(sys.argv[3]), float(sys.argv[4]))
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
