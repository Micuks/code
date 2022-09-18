from turtle import numinput
import numpy as np

from layers import *
from gradient_check import *
from layer_test_utils import *


seed = 576


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

    print('Testing conv_forward_naive function')
    print('difference: ', rel_error(out, correct_out))


def conv_backward_naive_test():
    ''' Test the implementation of conv_backward_naive '''
    np.random.seed(seed)
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
        lambda w: conv_forward_naive(x, w, b, conv_param)[0], w, dout)
    db_num = eval_numerical_gradient_array(
        lambda b: conv_forward_naive(x, w, b, conv_param)[0], b, dout)

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
    np.random.seed(seed)
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


def batchnorm_forward_test():
    '''
    Test the implementation of batch normalization forward pass.

    Check the **training-time** forward pass by checking means and variances
    of features both before and after batch normalization.

    Check the **test-time** forward pass by running the training-time
    forward pass many times to warm up the running averages, and then
    checking the means and variances of activations after a test-time
    forward pass.
    '''
    # training-time test
    np.random.seed(seed)
    N, D1, D2, D3 = 200, 50, 60, 3
    X = np.random.randn(N, D1)
    W1 = np.random.randn(D1, D2)
    W2 = np.random.randn(D2, D3)
    a = np.maximum(0, X.dot(W1)).dot(W2)

    print('Before batch normalization:')
    print_mean_std(a, axis=0)

    gamma = np.ones((D3,))
    beta = np.zeros(D3,)

    # Means should beclose to zero and stds close to one
    print('After batch normalization (gamma=1, beta=0)')
    a_norm, _ = batchnorm_forward(a, gamma, beta, {'mode': 'train'})
    print_mean_std(a_norm, axis=0)

    gamma = np.asarray([1.0, 2.0, 3.0])
    beta = np.asarray([11.0, 12.0, 13.0])

    # Now means should be closed to beta and stds close to gamma
    print(f'After batch normalization (gamma={gamma}, beta={beta})')
    a_norm, _ = batchnorm_forward(a, gamma, beta, {'mode': 'train'})
    print_mean_std(a_norm, axis=0)

    # test-time test
    # reinitialize W1 and W2 with seed the same as in traing-time test
    W1 = np.random.randn(D1, D2)
    W2 = np.random.randn(D2, D3)

    bn_param = {'mode': 'train'}
    gamma = np.ones(D3)
    beta = np.zeros(D3)

    # run 50 epochs in training mode to warm up the running averages
    for t in range(50):
        # affine - relu - affine - batchnorm
        X = np.random.randn(N, D1)
        a = np.maximum(0, X.dot(W1)).dot(W2)
        batchnorm_forward(a, gamma, beta, bn_param)

    bn_param['mode'] = 'test'
    X = np.random.randn(N, D1)
    a = np.maximum(0, X.dot(W1)).dot(W2)
    a_norm, _ = batchnorm_forward(a, gamma, beta, bn_param)

    # Means should be close to zero and stds close to one, but will be
    # noisier than training-time forward passes for running averages is
    # less accuracy than directly calculate mean and variance on dataset
    print('After batch normalization (test-time):')
    print_mean_std(a_norm, axis=0)


def batchnorm_backward_test():
    '''
    Test the implementation of batch normalization backward pass using
    gradient check.
    '''
    np.random.seed(seed)
    N, D = 4, 5
    x = 5 * np.random.randn(N, D) + 12
    gamma = np.random.randn(D)
    beta = np.random.randn(D)
    dout = np.random.randn(N, D)

    bn_param = {'mode': 'train'}
    def fx(x): return batchnorm_forward(x, gamma, beta, bn_param)[0]
    def fg(a): return batchnorm_forward(x, a, beta, bn_param)[0]
    def fb(b): return batchnorm_forward(x, gamma, b, bn_param)[0]

    dx_num = eval_numerical_gradient_array(fx, x, dout)
    da_num = eval_numerical_gradient_array(fg, gamma.copy(), dout)
    db_num = eval_numerical_gradient_array(fb, beta.copy(), dout)

    _, cache = batchnorm_forward(x, gamma, beta, bn_param)
    dx, dgamma, dbeta = batchnorm_backward(dout, cache)

    # It is expected to see relative errors between 1e-13 and 1e-8
    print('dx error: ', rel_error(dx_num, dx))
    print('dgamma error: ', rel_error(da_num, dgamma))
    print('dbeta error: ', rel_error(db_num, dbeta))


def spatial_bachnorm_forward_test():
    '''
    Test the implementation of spatial batch normalization
    (also known as batchnorm2d).

    Check the training-time forward pass by checking means and
    variances of features both before and after spatial batch
    normalization.

    Check the test-time forward pass by running the training-time
    forward pass many times to warm up the running averages, and
    then checking the means and variances of activations after a
    test-time forward pass.
    '''
    np.random.seed(seed)

    # training-time test
    N, C, H, W = 2, 3, 4, 5
    x = 4 * np.random.randn(N, C, H, W) + 10

    print('Before spatial batch normalization:')
    print(' shape: ', x.shape)
    # calculate means and stds of dimentions N, H and W
    print(' means: ', x.mean(axis=(0, 2, 3)))
    print(' stds: ', x.std(axis=(0, 2, 3)))

    # Means should be closed to zero and stds close to one
    gamma, beta = np.ones(C), np.zeros(C)
    bn_param = {'mode': 'train'}
    out, _ = spatial_batchnorm_forward(x, gamma, beta, bn_param)
    print('After spatial batch normalization:')
    print(' shape: ', out.shape)
    print(' means: ', out.mean(axis=(0, 2, 3)))
    print(' stds: ', out.std(axis=(0, 2, 3)))

    # Means should be closed to beta and stds close to gamma
    gamma, beta = np.asarray([3, 4, 5]), np.asarray([6, 7, 8])
    out, _ = spatial_batchnorm_forward(x, gamma, beta, bn_param)
    print('After spatial batch normalization (nontrivial gamma, beta):')
    print(' shape: ', out.shape)
    print(' means: ', out.mean(axis=(0, 2, 3)))
    print(' std: ', out.std(axis=(0, 2, 3)))

    # test-time test
    N, C, H, W = 10, 4, 11, 12
    bn_param = {'mode': 'train'}
    gamma = np.ones(C)
    beta = np.zeros(C)
    # run training for 50 epochs
    for t in range(50):
        x = 2.3 * np.random.randn(N, C, H, W) + 13
        spatial_batchnorm_forward(x, gamma, beta, bn_param)
    bn_param['mode'] = 'test'
    x = 2.3 * np.random.randn(N, C, H, W) + 13
    a_norm, _ = spatial_batchnorm_forward(x, gamma, beta, bn_param)

    # Means should be close to zero and stds close to one, but will be
    # noiser than training-time forward passes, for the running averages
    # are less accurate than averages calculated on entire training set
    print('After spatial batch normalization (test-time):')
    print(' means: ', a_norm.mean(axis=(0, 2, 3)))
    print(' stds: ', a_norm.std(axis=(0, 2, 3)))


def spatial_batchnorm_backward_test():
    '''
    Test the implementation of spatial batch normalization
    '''
    np.random.seed(seed)

    N, C, H, W = 2, 3, 4, 5
    x = 5 * np.random.randn(N, C, H, W) + 12
    gamma = np.random.randn(C)
    beta = np.random.randn(C)
    dout = np.random.randn(N, C, H, W)

    bn_param = {'mode': 'train'}
    def fx(x): return spatial_batchnorm_forward(x, gamma, beta, bn_param)[0]

    def fg(a): return spatial_batchnorm_forward(
        x, a, beta, bn_param)[0]  # TODO replace gamma with a ?

    def fb(b): return spatial_batchnorm_forward(
        x, gamma, b, bn_param)[0]  # TODO replace beta with b?

    dx_num = eval_numerical_gradient_array(fx, x, dout)
    da_num = eval_numerical_gradient_array(fg, gamma, dout)
    db_num = eval_numerical_gradient_array(fb, beta, dout)

    # It is expected to have errors of magnitudes metween 1e-12~1e-6
    _, cache = spatial_batchnorm_forward(x, gamma, beta, bn_param)
    dx, dgamma, dbeta = spatial_batchnorm_backward(dout, cache)
    print('dx_error: ', rel_error(dx_num, dx))
    print('dgamma error: ', rel_error(da_num, dgamma))
    print('dbeta error: ', rel_error(db_num, dbeta))


def affine_forward_test():
    '''
    Test the implementation of affine forward pass.
    '''
    num_inputs = 2
    input_shape = (4, 5, 6)
    output_dim = 3
    input_size = num_inputs * np.prod(input_shape)
    weight_size = output_dim * np.prod(input_shape)

    x = np.linspace(-0.1, 0.5,
                    num=input_size).reshape(num_inputs, *input_shape)
    w = np.linspace(-0.2, 0.3,
                    num=weight_size).reshape(np.prod(input_shape), output_dim)
    b = np.linspace(-0.3, 0.1, num=output_dim)

    out, _ = affine_forward(x, w, b)
    correct_out = np.array([[1.49834967,  1.70660132,  1.91485297],
                            [3.25553199,  3.5141327,   3.77273342]])

    # The error should be around e-9 or less.
    print('Testing affine_forward function:')
    print('difference: ', rel_error(out, correct_out))


def affine_backward_test():
    '''
    Test the implementation of affine backward pass
    '''
    np.random.seed(seed)
    x = np.random.randn(10, 2, 3)
    w = np.random.randn(6, 5)
    b = np.random.randn(5)
    dout = np.random.randn(10, 5)

    dx_num = eval_numerical_gradient_array(
        lambda x: affine_forward(x, w, b)[0], x, dout)
    dw_num = eval_numerical_gradient_array(
        lambda w: affine_forward(x, w, b)[0], w, dout)
    db_num = eval_numerical_gradient_array(
        lambda b: affine_forward(x, w, b)[0], b, dout)

    _, cache = affine_forward(x, w, b)
    dx, dw, db = affine_backward(dout, cache)

    # The error shoule be around e-10 or less
    print('Testing affine_backward function:')
    print('dx error: ', rel_error(dx_num, dx))
    print('dw error: ', rel_error(dw_num, dw))
    print('db error: ', rel_error(db_num, db))


def relu_forward_test():
    '''
    Test the implementation of ReLU forward pass
    '''
    x = np.linspace(-0.5, 0.5, num=12).reshape(3, 4)
    out, _ = relu_forward(x)
    correct_out = np.array([[0.,          0.,          0.,          0., ],
                            [0.,          0.,          0.04545455,  0.13636364, ],
                            [0.22727273,  0.31818182,  0.40909091,  0.5, ]])

    # The error should be on the order of 1e-8
    print('Testing relu_forward function:')
    print(' difference: ', rel_error(out, correct_out))


def relu_backward_test():
    '''
    Test the implementation of ReLU backward pass
    '''
    np.random.seed(seed)
    x = np.random.randn(10, 10)
    dout = np.random.randn(*x.shape)

    # print shape of x and dout for debug
    # print(f'x.shape={x.shape}')
    # print(f'dout.shape(*x.shape)={np.asarray(dout).shape}')

    dx_num = eval_numerical_gradient_array(
        lambda x: relu_forward(x)[0], x, dout)
    _, cache = relu_forward(x)
    dx = relu_backward(dout, cache)

    # The error should be on the order of e-12
    print('Testing relu_backward function:')
    print('dx error: ', rel_error(dx_num, dx))


def softmax_loss_test():
    '''
    Test the implementation of softmax loss
    '''
    np.random.seed(seed)
    num_classes, num_inputs = 10, 50
    x = 0.001 * np.random.randn(num_inputs, num_classes)
    y = np.random.randint(num_classes, size=num_inputs)

    dx_num = eval_numerical_gradient(
        lambda x: softmax_loss(x, y)[0], x, verbose=False)
    loss, dx = softmax_loss(x, y)

    # Test softmax_loss function. Loss should be close to 2.3 and dx error should
    # be around e-8
    print('\nTesting softmax_loss:')
    print(' loss: ', loss)
    print(' dx error: ', rel_error(dx_num, dx))
