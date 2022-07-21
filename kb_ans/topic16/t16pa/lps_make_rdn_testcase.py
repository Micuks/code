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

import pickle

prime = []
P = 100000007
#P = 100000007


def fast_power(n, k):
    print("type of n: ", type(n), " type of k: ", type(k))
    ret = 1
    mul = n
    while k != 0:
        if k % 0x2:
            ret = (ret * mul) % P
        mul = (mul * mul) % P
        #k = k / 2
        k = k >> 1
    return ret


class Point:
    def Point(self, x_, y_):
        self.x = x_
        self.y = y_

    def __lt__(self, other):
        if self.x != other.x:
            return self.x < other.x
        return self.y < other.y


def main(file_name, case_cnt, block_path_ratio):
    global prime
    print("file_name:{}, case_cnt:{}, block_path_ratio:{}".format(
        file_name, case_cnt, block_path_ratio))
    with open(file_name, 'w') as f:
        f.write("1\n")
        s = ['a', 'b', 'c']
        cnt = random.randrange(1, 30)
        #print(" ".join(random.choices(s, k=cnt)))
        f.write("{}\n".format("".join(random.choices(s, k=cnt))))


if __name__ == "__main__":
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
