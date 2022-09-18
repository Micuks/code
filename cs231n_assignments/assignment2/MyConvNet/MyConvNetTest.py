import numpy as np
from MyConvNet import *
from MyConvNet import MyConvNet
from gradient_check import eval_numerical_gradient
from layer_test_utils import rel_error

seed = 576


def MyConvNetSanityCheckLoss(fast=False):
    '''
    Sanity check the loss. For softmax loss is used, it is expected
    that the loss for random weights (and no regularization) to be
    about log(C) for C classes. When regularization is used, the loss
    should go up slightly.
    '''

    # Use fast implementations of Conv2d and Maxpool
    if fast:
        print('Check fast implementation version')
    elif not fast:
        print('Check naive implementation version')

    model = MyConvNet(fast)

    N = 50
    C = 10
    X = np.random.randn(N, 3, 32, 32)
    y = np.random.randint(C, size=N)

    print(f'ln(10)={np.log(10)}')
    loss, grads = model.loss(X, y)
    print('Initial loss (no regularization): ', loss)

    model.reg = 0.5
    loss, grads = model.loss(X, y)
    print('Initial loss (with regularization): ', loss)


def MyConvNetGradientCheck(fast=False):
    '''
    Use numeric gradient checking to make sure that the backward pass is
    correct. When using numeric gradient checking, a small amount of
    artificial data and a small number of neurons at each layer is supposed
    to use.
    NOTE: correct implementations may still have relative errors up to the
    order of e-2.
    '''
    num_inputs = 2
    input_dim = (3, 16, 16)
    reg = 0.0
    num_classes = 10
    np.random.seed(seed)
    # concatenate input_dim.shape to randn's shape
    X = np.random.randn(num_inputs, *input_dim)
    y = np.random.randint(num_classes, size=num_inputs)

    model = MyConvNet(
        channel_1=3,
        filter_size_1=3,
        channel_2=3,
        filter_size_2=1,
        input_dim=input_dim,
        hidden_dim=7,
        fast=fast,
    )
    loss, grads = model.loss(X, y)
    # Errors should be small, but correct implementations may have relative errors up to the
    # order of e-2
    for param_name in sorted(grads):
        def f(_): return model.loss(X, y)[0]
        param_grad_num = eval_numerical_gradient(
            f, model.params[param_name], verbose=False, h=1e-6)
        e = rel_error(param_grad_num, grads[param_name])
        print('%s max relative error: %e' %
              (param_name, rel_error(param_grad_num, grads[param_name])))


if __name__ == '__main__':
    '''
    Can be executed directly for debug conveniently
    '''
    # MyConvNetSanityCheckLoss(fast=True)
    # MyConvNetSanityCheckLoss()
    MyConvNetGradientCheck(fast=True)
    # MyConvNetGradientCheck()
