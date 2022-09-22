import os
import sys
import numpy as np
# import cupy as np
import matplotlib.pyplot as plt
from time import time

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
    # print(f'Running layer implementation check...')
    # LayerTest()

    # Check MyConvNet overall implementation

    # Sanity check loss
    # print(f'Running sanity loss check...')
    # t0 = time()
    # MyConvNetSanityCheckLoss(fast=True)
    # t1 = time()
    # MyConvNetSanityCheckLoss()
    # t2 = time()
    # print('Testing speed of fast and naive conv and maxpool layer:')
    # print('Fast: %fs' % (t1 - t0))
    # print('Naive: %fs' % (t2 - t1))
    # print('Speedup: %fx' % ((t2 - t1) / (t1 - t0)))

    # Gradient check
    print(f'Running gradient check...')
    t0 = time()
    MyConvNetGradientCheck(fast=True)
    t1 = time()
    # MyConvNetGradientCheck()
    # t2 = time()
    # print('Testing speed of fast and naive conv and maxpool layer:')
    print('Fast: %fs' % (t1 - t0))
    # print('Naive: %fs' % (t2 - t1))
    # print('Speedup: %fx' % ((t2 - t1) / (t1 - t0)))

    # Small dataset overfit check
    print(f'Running small dataset overfit check...')
    t0 = time()
    MyConvNetOverfitCheck(data, fast=True)
    t1 = time()
    # MyConvNetOverfitCheck(data)
    t2 = time()
    print('Testing speed of fast and naive conv and maxpool layer:')
    print('Fast: %fs' % (t1 - t0))
    # print('Naive: %fs' % (t2 - t1))
    # print('Speedup: %fx' % ((t2 - t1) / (t1 - t0)))


def train(data={}, fast=False):
    ''' Train MyConvNet on dataset '''
    model = MyConvNet(weight_scale=1e-3,
                      reg=1e-3,
                      fast=fast,
                      )
    print(f'fast={fast}')
    solver = Solver(
        model,
        data,
        num_epochs=1,
        batch_size=50,
        update_rule='adam',
        optim_config={'learning_rate': 1e-3, },
        verbose=True,
        print_every=20,
    )

    return model, solver


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

    # Train MyConvNet
    # time0 = time()
    # final_model, final_solver = train(data=data, fast=True)
    # time1 = time()
    # print(
    #     'Full data training accuracy:',
    #     final_solver.check_accuracy(data['X_train'], data['y_train'])
    # )
    # print(
    #     'Full data validation accuracy:',
    #     final_solver.check_accuracy(data['X_val'], data['y_val'])
    # )
    # print('Training time cost: %fs' % (time1 - time0))


if __name__ == '__main__':
    main()
