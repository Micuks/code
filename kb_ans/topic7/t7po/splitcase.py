#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2020 zhangxianwen <zhangxianwen@LAPTOP-9POC3RUN>
#
# Distributed under terms of the MIT license.
"""

"""

import sys


def main(file_name):
    s1n = file_name + ".1"
    s2n = file_name + ".2"
    print("file_name: {}, s1name: {} s2name: {}".format(file_name, s1n, s2n))
    with open(file_name, 'r') as f:
        case_cnt = int(f.readline())
        rcnt = int(f.readline())
        s1num = int(rcnt / 2)
        s2num = rcnt - s1num
        with open(s1n, 'w') as f1:
            f1.write("{}\n{}\n".format(case_cnt, s1num))
            for _ in range(s1num):
                f1.write(f.readline())
        with open(s2n, 'w') as f2:
            f2.write("{}\n{}\n".format(case_cnt, s2num))
            for _ in range(s2num):
                f2.write(f.readline())


if __name__ == "__main__":
    main(sys.argv[1])
