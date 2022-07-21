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
import base64


def main(file_name, case_cnt, block_path_ratio):
    global prime
    print("file_name:{}, case_cnt:{}, block_path_ratio:{}".format(
        file_name, case_cnt, block_path_ratio))
    with open(file_name, 'w') as f:
        for _ in range(case_cnt):
            maxn = 512
            maxm = 128

            # maxn max count for virus
            maxn = 4
            # maxm max count for docs
            maxm = 4
            n = random.randrange(1, maxn)
            m = random.randrange(1, maxm)

            maxv = 64
            maxf = 2048

            # maxv max length for virus
            maxv = 4
            # maxv max length for docs
            #maxf = 4
            f.write("{}\n".format(n))
            bts = [x for x in range(256)]
            for x in range(n):
                f.write("{}\n".format(
                    base64.b64encode(
                        bytes(random.choices(bts, k=random.randrange(
                            1, maxv)))).decode()))
            f.write("{}\n".format(m))
            for x in range(m):
                f.write("{}\n".format(
                    base64.b64encode(
                        bytes(random.choices(bts, k=random.randrange(
                            1, maxf)))).decode()))

            #S = ['a', 'b', 'c']
            #s = [str(random.randrange(0, 20) - 10) for _ in range(n)]
            #t = [str(random.randrange(0, 20) - 10) for _ in range(m)]
            #s = random.choices(S, k=m)
            #f.write("{}\n".format("".join(s)))
            f.write("\n")


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
