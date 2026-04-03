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
    with open(file_name, 'w') as f:
        S = [chr(x + ord('a')) for x in range(ord('z') - ord('a') + 1)]
        f.write("{}\n".format(case_cnt))
        for _ in range(case_cnt):
            n = random.randrange(1, 50)
            m = random.randrange(1, 100)
            #n = random.randrange(1, 5)
            #m = random.randrange(1, 3)
            f.write("{} {}\n".format(n, m))
            sset = set()
            while len(sset) < m:
                dif = m - len(sset)
                dif_s = set()
                for _ in range(dif):
                    l = random.randrange(1, 11)
                    #l = random.randrange(1, 6)
                    s = "".join(random.choices(S, k=l))
                    dif_s.add(s)
                    #f.write("{}\n".format(s))
                sset.update(dif_s)
            for s in sset:
                f.write("{}\n".format(s))
            v = [x for x in range(1, 100)]
            s = " ".join(str(x) for x in random.choices(v, k=m))
            f.write("{}\n".format(s))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
