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
    case_cnt = 3
    print("file_name:{}, case_cnt:{}, block_path_ratio:{}".format(
        file_name, case_cnt, block_path_ratio))
    #max_ab = 10**200
    max_ab = 10**3
    #max_ab = 20
    with open(file_name, 'w') as f:
        S = ['0', '1']
        f.write("{}\n".format(case_cnt))
        for _ in range(case_cnt):
            #n = random.randrange(1, 1e2)
            n = random.randrange(1, 5)
            #n = 100
            f.write("{}\n".format(n))
            es = set()
            for x in range(n):
                #err_len = random.randrange(1, 21)
                err_len = random.randrange(1, 5)
                #err_len = 20
                s = "".join(random.choices(S, k=err_len))
                while s in es:
                    s = "".join(random.choices(S, k=err_len))
                es.add(s)
                f.write("{}\n".format(s))

            A = random.randrange(1, max_ab)
            B = random.randrange(1, max_ab)
            A, B = min(A, B), max(A, B)
            f.write("{} {}\n".format(A, B))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
