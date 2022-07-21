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
        N = int(random.randrange(1, 100))
        M = int(random.randrange(1, 100))
        K = int(random.randrange(1, 100))
        B = int(random.randrange(1, 20))
        pts = []
        rem = 1
        while len(pts) != B:
            p = (random.randrange(1, M+1), random.randrange(1, N+1))
            #p = Point(random.randrange(1, M+1), random.randrange(1, N+1))
            if p in pts:
                continue
            pts.append(p)
        pts.sort()
        for j in range(1, M+1):
            if [1, j] not in pts:
                rem = (rem * K) % P

        km1p = int(M*N - B)
        print("type of km1p: ", type(km1p))
        kp = 0
        ff_bcnt = 0

        for p in pts:
            if p[0] != M and [p[0]+1, p[1]] not in pts:
                kp += 1
        kp += N
        for p in pts:
            if p[0] == M:
                kp -= 1

        km1p = km1p - kp

        print("type of kp: ", type(kp), " type of km1p: ", type(km1p))
        rem = (fast_power(K, kp) * fast_power(K-1, km1p)) % P
        R = rem

        #R = random.randrange(0, 1e8+7)

        f.write("{} {} {} {}\n".format(N, K, B, R))
        for p in pts:
            f.write("{} {}\n".format(p[0], p[1]))
        print("case generated, M: ", M, " kp: ", kp, " km1p: ", km1p)

        '''
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
        '''


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
    #p_name = "../prime.pickle"
    #make_prime(int(1e6+3), p_name)
    #load_prime(p_name)
    main(sys.argv[1], int(sys.argv[2]), float(sys.argv[3]))
