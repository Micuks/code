import numpy as np
# import cupy as np


def rel_error(x, y):
    ''' Returns relative error. '''
    return np.max(np.abs(x - y) / np.maximum(1e-8, np.abs(x) + np.abs(y)))


def print_mean_std(x, axis=0):
    print(f'  means: {x.mean(axis=axis)}')
    print(f'  std:   {x.std(axis=axis)}\n')