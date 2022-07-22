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
    print("file_name:{}, case_cnt:{}, block_path_ratio:{}".format(file_name, case_cnt, block_path_ratio))
    with open(file_name, 'w') as f:
        for case_idx in range(case_cnt):
            l = random.randrange(1, 7)
            r = random.randrange(1, 7)
            c = random.randrange(1, 7)
            si = 1 if l == 1 else random.randrange(1, l)
            sj = 1 if r == 1 else random.randrange(1, r)
            sk = 1 if c == 1 else random.randrange(1, c)
            ei = 1 if l == 1 else random.randrange(1, l)
            ej = 1 if r == 1 else random.randrange(1, r)
            ek = 1 if c == 1 else random.randrange(1, c)
            while ei != si and ej != sj and ek != sk:
                ei = 1 if l == 1 else random.randrange(1, l)
                ej = 1 if r == 1 else random.randrange(1, r)
                ek = 1 if c == 1 else random.randrange(1, c)
            f.write('{} {} {}\n'.format(l, r, c));
            for i in range(l):
                for j in range(r):
                    s = ''
                    for k in range(c):
                        if i+1 == si and j+1 == sj and k+1 == sk:
                            s += 'S'
                        elif i+1 == ei and j+1 == ej and k+1 == ek:
                            s += 'E'
                        else:
                            s += '.' if random.uniform(0, 1) < block_path_ratio else '#'
                    f.write('{}\n'.format(s))
                f.write('\n')

if __name__ == "__main__":
    #main(sys.argv[2], int(sys.argv[3]), float(sys.argv[4]))
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))