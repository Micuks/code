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


class UnionSet:
    def __init__(self, n):
        self.pa = list(range(n + 1))

    def find(self, x):
        if self.pa[x] == x:
            return x
        else:
            newpa = self.find(self.pa[x])
            self.pa[x] = newpa
            return newpa

    def add(self, x, y):
        fx = self.find(x)
        fy = self.find(y)
        if fx == fy:
            return
        else:
            self.pa[fy] = fx
            return


def main(file_name, case_cnt, block_path_ratio):
    case_cnt = 1
    print("file_name:{}, case_cnt:{}, block_path_ratio:{}".format(
        file_name, case_cnt, block_path_ratio))
    with open(file_name, 'w') as f:
        for _ in range(case_cnt):
            n = random.randrange(2, 1e1)
            m = random.randrange(n + 1, 2e1)
            f.write("{} {}\n".format(n, m))
            print("n:{} m:{}\n".format(n, m))
            us = UnionSet(n)
            for i in range(m - n):
                a = random.randrange(1, n + 1)
                b = random.randrange(1, n + 1)
                while (a == b):
                    b = random.randrange(1, n + 1)
                us.add(a, b)
                f.write("{} {}\n".format(a, b))
            u1 = us.find(1)
            for i in range(1, n + 1):
                f.write("{} {}\n".format(i, 1))
                if us.find(i) != u1:
                    us.add(i, 1)
            q = random.randrange(1, 1e1)
            print("q:{}\n".format(q))
            f.write("{}\n".format(q))
            for i in range(q):
                a = random.randrange(1, n + 1)
                b = random.randrange(1, n + 1)
                while (a == b):
                    b = random.randrange(1, n + 1)
                f.write("{} {}\n".format(a, b))
        f.write("0 0\n")


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
