import os
import platform
import numpy as np
# import cupy as np
from six.moves import cPickle as pickle


def load_pickle(f):
    version = platform.python_version_tuple()
    if version[0] == '3':
        return pickle.load(f, encoding='latin1')
    raise ValueError('invalid python version: {}'.format(version))


def load_CIFAR_batch(filename):
    ''' load single batch of cifar '''
    with open(filename, 'rb') as f:
        datadict = load_pickle(f)
        X = np.asarray(datadict['data'])
        Y = np.asarray(datadict['labels'])
        X = X.reshape(10000, 3, 32, 32).transpose(
            0, 2, 3, 1).astype('float')  # N, C, H, W to N, H, W, C
        Y = np.array(Y)
        return X, Y


def load_CIFAR10(ROOT):
    ''' load all of cifar '''
    xs = []
    ys = []
    for b in range(1, 6):
        f = os.path.join(ROOT, 'data_batch_%d' % (b,))
        X, Y = load_CIFAR_batch(f)
        xs.append(X)
        ys.append(Y)
    Xtr = np.concatenate(np.asarray(xs))
    Ytr = np.concatenate(np.asarray(ys))
    del X, Y
    Xte, Yte = load_CIFAR_batch(os.path.join(ROOT, 'test_batch'))
    return Xtr, Ytr, Xte, Yte


def get_CIFAR10_data(
    num_training=49000, num_validation=1000, num_test=1000, subtract_mean=True
):
    '''
    Load the CIFAR-10 dataset and perform preprocessing to prepare it for
    classifiers. Condensed to a single function.
    '''
    # Load the raw CIFAR-10 data
    cifar10_dir = os.path.join(
        os.path.dirname(__file__), 'datasets/cifar-10-batches-py'
    )
    X_train, y_train, X_test, y_test = load_CIFAR10(cifar10_dir)

    # Subsample the data
    mask = list(range(num_training, num_training + num_validation))
    X_val = X_train[mask]
    y_val = y_train[mask]
    mask = list(range(num_training))
    X_train = X_train[mask]
    y_train = y_train[mask]
    mask = list(range(num_test))
    X_test = X_test[mask]
    y_test = y_test[mask]

    # Normalize the data: subtract the mean image
    # calculated from training set
    if subtract_mean:
        mean_image = np.mean(X_train, axis=0)
        X_train -= mean_image
        X_val -= mean_image
        X_test -= mean_image

    # Transpose to let channels come first
    # Transpose from N, H, W, C to N, C, H, W
    X_train = X_train.transpose(0, 3, 1, 2).copy()
    X_val = X_val.transpose(0, 3, 1, 2).copy()
    X_test = X_test.transpose(0, 3, 1, 2).copy()

    # Package data into a dict
    return {
        'X_train': X_train,
        'y_train': y_train,
        'X_val': X_val,
        'y_val': y_val,
        'X_test': X_test,
        'y_test': y_test,
    }