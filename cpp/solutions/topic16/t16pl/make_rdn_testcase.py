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
        f.write("{}\n".format(case_cnt))
        for _ in range(case_cnt):
            s = [chr(x) for x in range(ord('a'), ord('z') + 1)]
            random.shuffle(s)
            f.write("{}\n".format("".join(s)))
            n = random.randrange(1, 1e3)
            ori = random.choices(s, k=n)
            dec = []
            for x in ori:
                dec.append(s[ord(x) - ord('a')])
            strip = random.randrange(1, n + 1)
            sarr = ori[:strip]
            f.write("{}\n".format("".join(dec + sarr)))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
