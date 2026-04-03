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


def main(file_name, case_cnt, block_path_ratio):
    global prime
    print("file_name:{}, case_cnt:{}, block_path_ratio:{}".format(
        file_name, case_cnt, block_path_ratio))
    with open(file_name, 'w') as f:
        c = random.randrange(1, 10)
        s = random.randrange(1, 11)
        f.write("{} {}\n".format(c, s))
        s = set()
        for _ in range(c):
            #prime_upper_bound = len(prime) - 1
            prime_upper_bound = 30
            print("pub: ", prime_upper_bound)
            x = random.randrange(1, prime_upper_bound)
            while(x in s):
                x = random.randrange(1, prime_upper_bound)
            s.add(x)
            k = random.randrange(1, min(100, prime[x]))
            rc = [str(x) for x in random.sample(range(0, prime[x]), k)]
            rs = " ".join(rc)
            f.write("{} {} {}\n".format(prime[x], k, rs))

        f.write("0 0\n")


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
    print("make prime pickle is done, prime length: ",
          len(prime), " content: ", prime[0:10])
    with open(file_name, "wb") as f:
        pickle.dump(prime, f)


def load_prime(file_name):
    global prime
    with open(file_name, "rb") as f:
        prime = pickle.load(f)
    print("load prime pickle is done, prime length: ",
          len(prime), " content: ", prime[0:10])


if __name__ == "__main__":
    #main(sys.argv[2], int(sys.argv[3]), float(sys.argv[4]))
    p_name = "prime.pickle"
    #make_prime(int(1e6+3), p_name)
    load_prime(p_name)
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
