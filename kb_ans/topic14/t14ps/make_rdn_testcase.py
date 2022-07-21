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
        k = random.randrange(1, 4)
        a = random.randrange(0, 2**k)
        b = random.randrange(0, 2**k)
        c = random.randrange(0, 2**k)
        f.write("{} {} {} {}\n".format(a, b, c, k))
        f.write("0 0 0 0\n")


def make_prime(ub, file_name):
    not_prime = [0] * ub
    prime = []
    pcnt = 0
    for i in range(2, ub):
        if not_prime[i] == 0:
            prime.append(i)
            pcnt += 1
        for j in range(pcnt):
            if prime[j] * i > ub:
                break
            not_prime[prime[j] * i] = 1
            if i % prime[j] == 0:
                break
    print("make prime pickle is done, prime length: ", len(prime),
          " content: ", prime[0:10])
    with open(file_name, "wb") as f:
        pickle.dump(prime, f)


def load_prime(file_name):
    global prime
    with open(file_name, "rb") as f:
        prime = pickle.load(f)
    print("load prime pickle is done, prime length: ", len(prime),
          " content: ", prime[0:10])


if __name__ == "__main__":
    #main(sys.argv[2], int(sys.argv[3]), float(sys.argv[4]))
    #p_name = "../prime.pickle"
    #make_prime(int(1e6+3), p_name)
    #load_prime(p_name)
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
