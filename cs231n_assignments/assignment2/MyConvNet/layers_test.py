import numpy as np

from MyConvNet.layers import *
from MyConvNet.gradient_check import *


def rel_error(x, y):
    ''' return relative error '''
    return np.max(np.abs(x-y)/(np.maximum(1e-8, np.abs(x)+np.abs(y))))


def conv_forward_naive_test():
    ''' Test the implementation of conv_forward_naive '''
    # TODO migrate to test the implementation of conv_forward_fast
    # and remove hard encode part

    x_shape = (2, 3, 4, 4)
    w_shape = (3, 3, 4, 4)
    x = np.linspace(-0.1, 0.5, num=np.prod(x_shape)).reshape(x_shape)
    w = np.linspace(-0.2, 0.3, num=np.prod(w_shape)).reshape(w_shape)
    b = np.linspace(-0.1, 0.2, num=3)

    conv_param = {'stride': 2, 'pad': 1, }
    out, _ = conv_forward_naive(x, w, b, conv_param)
    correct_out = np.array([[[[-0.08759809, -0.10987781],
                              [-0.18387192, -0.2109216]],
                             [[0.21027089,  0.21661097],
                              [0.22847626,  0.23004637]],
                             [[0.50813986,  0.54309974],
                              [0.64082444,  0.67101435]]],
                            [[[-0.98053589, -1.03143541],
                              [-1.19128892, -1.24695841]],
                             [[0.69108355,  0.66880383],
                                [0.59480972,  0.56776003]],
                             [[2.36270298,  2.36904306],
                                [2.38090835,  2.38247847]]]])

    print('Testing conv_forward_naive')
    print('difference: ', rel_error(out, correct_out))


def conv_backward_naive_test():
    ''' Test the implementation of conv_backward_naive '''
    np.random.seed(576)  # if there is bug, give it a try to change it to 231
    # normalized distribution
    x = np.random.randn(4, 3, 5, 5)
    w = np.random.randn(2, 3, 3, 3)
    b = np.random.randn(2,)
    dout = np.random.randn(4, 2, 5, 5)
    conv_param = {'stride': 1, 'pad': 1}

    # numerial backprop
    dx_num = eval_numerical_gradient_array(
        lambda x: conv_forward_naive(x, w, b, conv_param)[0], x, dout)
    dw_num = eval_numerical_gradient_array(
        lambda w: conv_forward_naive(w, w, b, conv_param)[0], w, dout)
    db_num = eval_numerical_gradient_array(
        lambda b: conv_forward_naive(b, w, b, conv_param)[0], b, dout)

    out, cache = conv_forward_naive(x, w, b, conv_param)
    dx, dw, db = conv_backward_naive(dout, cache)

    # errors should be around e-8 or less
    print('Testing conv_backward_naive function')
    print('dx error: ', rel_error(dx, dx_num))
    print('dw error: ', rel_error(dw, dw_num))
    print('db error: ', rel_error(db, db_num))


def max_pool_forward_naive_test():
    ''' Test the implementation of max_pool_forward_naive '''
    x_shape = (2, 3, 4, 4)
    x = np.linspace(-0.3, 0.4, num=np.prod(x_shape)).reshape(x_shape)
    pool_param = {'pool_width': 2, 'pool_height': 2,
                  'stride': 2}  # use default pad=0

    out, _ = max_pool_forward_naive(x, pool_param)
    correct_out = np.array([[[[-0.26315789, -0.24842105],
                            [-0.20421053, -0.18947368]],
        [[-0.14526316, -0.13052632],
         [-0.08631579, -0.07157895]],
        [[-0.02736842, -0.01263158],
         [0.03157895,  0.04631579]]],
        [[[0.09052632,  0.10526316],
          [0.14947368,  0.16421053]],
         [[0.20842105,  0.22315789],
         [0.26736842,  0.28210526]],
         [[0.32631579,  0.34105263],
         [0.38526316,  0.4]]]])

    # compare output with above. Difference should be on the order of 1e-8
    print('Testing max_pool_forward_naive function:')
    print('difference: ', rel_error(out, correct_out))


def max_pool_backward_naive_test():
    ''' Test the implementation of max_pool_backward_naive '''
    np.random.seed(576)  # if there is bug, give it a try to change it to 231
    x = np.random.rand(3, 2, 8, 8)
    dout = np.random.randn(3, 2, 4, 4)
    pool_param = {'pool_height': 2, 'pool_width': 2,
                  'stride': 2}  # use defult pad=0

    dx_num = eval_numerical_gradient_array(
        lambda x: max_pool_forward_naive(x, pool_param)[0], x, dout)

    out, cache = max_pool_forward_naive(x, pool_param)
    dx = max_pool_backward_naive(dout, cache)

    # error shule be on the order of e-12
    print('Testing max_pool_backward_naive function:')
    print('dx error: ', rel_error(dx, dx_num))
