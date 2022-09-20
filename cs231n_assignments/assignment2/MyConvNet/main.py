import os
import sys
import numpy as np
# import cupy as np
import matplotlib.pyplot as plt

from data_utils import *
from layers_test import *
from MyConvNet import *
from MyConvNetTest import *


def setup_im2col():
    '''
    setup im2col for fast implementation of Conv2d and MaxPool.
    '''
    print('Setting up im2col with cython...')
    cmd = 'python setup.py build_ext --inplace'
    os.system(cmd)
    print('Successfully setup im2col.')


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

    
def test(data=dict()):
    ''' Test implementations of layers and model '''
    # Check MyConvNet layer implementations
    # LayerTest()

    # Check MyConvNet overall implementation

    # Sanity check loss
    # MyConvNetSanityCheckLoss(fast=True)
    # MyConvNetSanityCheckLoss()

    # Gradient check
    # MyConvNetGradientCheck(fast=True)
    # MyConvNetGradientCheck()

    # Small dataset overfit check
    MyConvNetOverfitCheck(data, fast=True)
    # MyConvNetOverfitCheck(data)


def main():
    init()
    # Load the preprocessed CIFAR-10 data
    data = get_CIFAR10_data()
    print('shape of data:')
    for k, v in list(data.items()):
        print(f'{k}: {v.shape}')

    # Setup im2col cython extension for Conv2d and maxpool
    setup_im2col()

    # Test implementations
    test(data)

if __name__ == '__main__':
    main()
