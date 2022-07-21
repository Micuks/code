#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2019 zhangxianwen <zhangxianwen@zhangxianwen-localhost>
#
# Distributed under terms of the MIT license.
# 2019-12-03 22:51

from subprocess import Popen, PIPE, STDOUT
import sys

make_rdn_cmd = "./make_rdn_testcase.py 'rdn_in' 10 0.3"
given_case = "1\n3\n0000\n111\n1100\n{} {}\n"

#make_rdn_cmd = ""
bin_name = 't17pn_unittest'
std_run = "./{}.std < iter_in".format(bin_name)
err_run = "./{}.err < iter_in".format(bin_name)


def main():
    idx = 0
    st = 95
    ed = 748
    while st + idx <= ed:
        print("{}th run".format(idx))
        cmd = 'echo "{}" > iter_in'.format(given_case.format(st, st + idx))
        idx += 1
        p = Popen(cmd,
                  shell=True,
                  stdin=PIPE,
                  stdout=PIPE,
                  stderr=STDOUT,
                  close_fds=True)
        res = p.stdout.read()
        p = Popen(std_run,
                  shell=True,
                  stdin=PIPE,
                  stdout=PIPE,
                  stderr=STDOUT,
                  close_fds=True)
        std_output = p.stdout.read().decode("utf-8")
        p = Popen(err_run,
                  shell=True,
                  stdin=PIPE,
                  stdout=PIPE,
                  stderr=STDOUT,
                  close_fds=True)
        err_output = p.stdout.read().decode("utf-8")
        if std_output.strip() != err_output.strip():
            print("err:\n{}std:\n{}\n".format(err_output, std_output))
            sys.exit(1)


if __name__ == "__main__":
    main()
