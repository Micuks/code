from asyncio import subprocess
import os
import sys
import numpy as np
import matplotlib.pyplot as plt
from data_utils import *
from layers_test import *


def init():
    ''' Initialize dataset '''
    # initialize dataset
    FOLDERNAME = os.getcwd()
    # print(f'FOLDERNAME={FOLDERNAME}')
    sys.path.append(FOLDERNAME)
    print('Importing dataset...')
    # os.system('cd $FOLDERNAME/datasets')
    os.chdir(FOLDERNAME+'/datasets')
    cmd = 'bash '+FOLDERNAME+'/datasets/get_datasets.sh'
    os.system(cmd)
    os.chdir(FOLDERNAME)
    print('Successfully imported CIFAR-10 dataset.\n')

    # initialize matplotlib
    plt.rcParams['figure.figsize'] = (10.0, 8.0)  # set default size of plots
    plt.rcParams['image.cmap'] = 'gray'


def test():
    '''
    Test the implementation of all layers and activation functions,
    both forward pass and backward pass.

    Layers:
    - Conv2d:
        - conv_forward_naive
        - conv_backward_naive
    - MaxPooling:
        - max_pool_forward_naive
        - max_pool_backward_naive
    - Batch Normalization (also known as BatchNorm1d):
        - batchnorm_forward
        - batchnorm_backward
    - Spatial Batch Normalization (also known as BatchNorm2d):
        - spatial_batchnorm_forward
        - spatial_batchnorm_backward
    - Affine (also known as Fully-Connected):
        - affine_forward
        - affine_backward
    - ReLU:
        - relu_forward
        - relu_backward
    - Softmax Loss Function:
        - softmax_loss
    '''
    print('Test the implementation of all layers.')

    print('Affine layer test:')
    # print('Forward pass:')
    affine_forward_test()
    # print('Backward pass:')
    affine_backward_test()

    print('ReLU test:')
    # print('Forward pass:')
    relu_forward_test()
    # print('Backward pass:')
    relu_backward_test()

    print('Softmax loss function test:')
    softmax_loss_test()

    print('Batch normalization (also known as BatchNorm1d) test:')
    # print('Forward pass:')
    batchnorm_forward_test()
    # print('Backward pass:')
    batchnorm_backward_test()

    print('Conv2d:')
    # print('Forward pass:')
    conv_forward_naive_test()
    # print('Backward pass:')
    conv_backward_naive_test()

    print('MaxPooling test:')
    # print('Forward pass:')
    max_pool_forward_naive_test()
    # print('Backward pass:')
    max_pool_backward_naive_test()

    print('Spatial Batch Normalization (also known as BatchNorm2d) test:')
    # print('Forward pass:')
    spatial_bachnorm_forward_test()
    # print('Backward pass:')
    spatial_batchnorm_backward_test()


def main():
    init()
    # Load the preprocessed CIFAR-10 data
    data = get_CIFAR10_data()
    print('shape of data:')
    for k, v in list(data.items()):
        print(f'{k}: {v.shape}')
    test()


if __name__ == '__main__':
    main()
