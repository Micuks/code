import numpy as np
from MyConvNet import *
from solver import *
from layer_test_utils import *
from layers import *
from layers_test import *
from gradient_check import eval_numerical_gradient
from layer_test_utils import rel_error

seed = 576

def LayerTest():
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
    num_inputs = 10
    input_dim = (3, 32, 32)
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


def MyConvNetOverfitCheck(data={}, fast=False):
    '''
    Train the model with just a few training samples is a nice trick. Small
    datasets should be overfitted, which will result in very high training
    accuracy and comparatively low validation accuracy.
    '''
    np.random.seed(seed)

    num_train = 100
    small_data = {
        'X_train': data['X_train'][:num_train],
        'y_train': data['y_train'][:num_train],
        'X_val': data['X_val'],
        'y_val': data['y_val'],
    }

    model = MyConvNet(
        weight_scale=1e-2,
        fast=fast,
    )

    solver = Solver(
        model, 
        small_data,
        num_epochs=15,
        batch_size=50,
        update_rule='adam',
        optim_config={'learning_rate': 5e-4,},
        verbose=True,
        print_every=1,
    )
    solver.train()

if __name__ == '__main__':
    '''
    Can be executed directly for debug conveniently
    '''
    # MyConvNetSanityCheckLoss(fast=True)
    MyConvNetSanityCheckLoss()
    # MyConvNetGradientCheck(fast=True)
    MyConvNetGradientCheck()
