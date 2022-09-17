import os
import sys
import numpy as np
import matplotlib.pyplot as plt
from MyConvNet.data_utils import *


def init():
    # initialize dataset
    FOLDERNAME = os.getcwd()
    sys.path.append(FOLDERNAME)
    os.system('cd $FOLDERNAME/datasets')
    os.system('bash get_datasets.sh')
    os.system('cd $FOLDERNAME/')

    # initialize matplotlib
    plt.rcParams['figure.figsize'] = (10.0, 8.0)  # set default size of plots
    plt.rcParams['image.cmap'] = 'gray'

    

def main():
    init()
    # Load the preprocessed CIFAR-10 data
    data = get_CIFAR10_data()
    for k, v in list(data.items()):
        print(f'{k}: {v.shape}')



if __name__ == '__main__':
    main()
