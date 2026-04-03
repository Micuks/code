#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2021 zhangxianwen <zhangxianwen@Ubuntu-WSL2>
#
# Distributed under terms of the MIT license.
"""

"""

with open('testin', 'w') as f:
    f.write('200 30 15\n')
    for i in range(230):
        for j in range(230):
            if i == j:
                f.write('0 ')
            else:
                f.write('200 ')
        f.write('\n')
