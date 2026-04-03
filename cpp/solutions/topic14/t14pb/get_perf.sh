#! /bin/bash
#
# get_perf.sh
# Copyright (C) 2020 zhangxianwen <zhangxianwen@zhangxianwen-localhost>
#
# Distributed under terms of the MIT license.
#


./t14pb_unittest < rdn_in &
sudo perf record -F 9999 -p $! -g -- sleep 20
sudo perf script > out.perf
