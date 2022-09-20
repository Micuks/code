import numpy as np
# import cupy as np

from layers import *
from layer_utils import *


class MyConvNet(object):
    '''
    A nine-layer convolutional network with the following architecture:

    [conv(3x3) - relu - maxpool(3x3)]x2 - [batchnorm2d - relu - conv(1x1)] -
    2x2 max pool - affine - relu - affine - softmax

    The network operates on minibatches of data that have shape (N, C, H, W)
    consisting of N images, each with height H and width W and with C input
    channels.
    '''

    def __init__(
        self,
        input_dim=(3, 32, 32),

        channel_1=256,
        filter_size_1=3,
        filter_pad_1=1,
        filter_stride_1=1,

        channel_2=32,
        filter_size_2=1,
        filter_pad_2=0,
        filter_stride_2=1,

        pool_size_1=3,
        pool_pad_1=0,  # try 1
        pool_stride_1=3,  # try 1

        pool_size_2=2,
        pool_pad_2=0,
        pool_stride_2=2,

        bn_momentum=0.1,  # TODO check whether it is unused.
        bn_eps=1e-5,  # TODO checker whether it is unused.

        hidden_dim=100,
        num_classes=10,
        weight_scale=1e-3,
        reg=0.0,
        dtype=np.float32,
        fast=False
    ):
        '''
        Initialize a new network.

        The inputs are mini batches of size N=64.

        Inputs:
        - input_dim: Tuple (C, H, W) giving size of input data.
        - channel_1: Number of filters to use in the 3x3 convolutional layer.
        - filter_size_1: Width/height of filters to use in the 3x3 convolutional layer.
        - filter_pad_1: Padding to use in the 3x3 convolutional layer.
        - filter_stride_1: Stride of filters to use in the 3x3 convolutional layer.

        - channel_2: Number of filters to use in the 1x1 convolutional layer.
        - filter_size_2: Width/height of filters to use in the 1x1 convolutional layer.
        - filter_size_2: Padding to use in the 1x1 convolutional layer.
        - filter_stride_2: Stride of filters to use in the 1x1 convolutional layer.

        - pool_size_1: Width/height of filters to use in the 3x3 maxpooling layer.
        - pool_pad_1: Padding to use in the 3x3 maxpooling layer.
        - pool_stride_1: Stride of filters to use in the 3x3 maxpooling layer.

        - pool_size_2: Width/height of filters to use in the 2x2 maxpooling layer.
        - pool_pad_2: Padding to use in the 2x2 maxpooling layer.
        - pool_stride_2: Stride of filters to use in the 2x2 maxpooling layer.

        - momentum: Momentum to use in spatial batch normalization layer.
        - eps: eps to use in spatial batch normalization layer to avoid numerical error.

        - hidden_dim: Number of units to use in the fully-connected hidden layer.
        - num_classes: Number of scores to produce from the final affine layer.
        - weight_scale: Scalar giving standard deviation for random initialization
            of weights.
        - reg: Scalar giving L2 regularization strength.
        - dtype: Numpy datatype to use for computaion.
        '''
        self.params = {}

        self.channel_1 = channel_1
        self.filter_size_1 = filter_size_1
        self.filter_pad_1 = filter_pad_1
        self.filter_stride_1 = filter_stride_1

        self.channel_2 = channel_2
        self.filter_size_2 = filter_size_2
        self.filter_pad_2 = filter_pad_2
        self.filter_stride_2 = filter_stride_2

        self.pool_size_1 = pool_size_1
        self.pool_pad_1 = pool_pad_1
        self.pool_stride_1 = pool_stride_1

        self.pool_size_2 = pool_size_2
        self.pool_pad_2 = pool_pad_2
        self.pool_stride_2 = pool_stride_2

        self.bn_momentum = bn_momentum
        self.bn_eps = bn_eps

        self.hidden_dim = hidden_dim,
        self.weight_scale = weight_scale

        self.reg = reg
        self.dtype = dtype

        self.fast = fast

        N = 64  # number of images in one mini batch
        C, H, W = input_dim

        ###########################################################################
        # Initialize weights and biases for the nine-layer convolutional network. #
        # Weights are initialized from a Gaussian centered at 0.0 with standard   #
        # deviation equal to weight_scale; biases are initialized to zero. All    #
        # weights and biases are stored in the dictionary self.params.            #
        ###########################################################################

        # [conv(3x3) - relu - maxpool(3x3)]x2 - [batchnorm2d - relu - conv(1x1)] -
        # 2x2 max pool - affine - relu - affine - softmax

        # conv_3_1(3x3)
        W_conv_3_1 = np.random.normal(loc=0.0, scale=weight_scale,
                                      size=(channel_1, C, filter_size_1, filter_size_1))
        b_conv_3_1 = np.zeros((channel_1,), dtype=float)

        WC_1 = (W + 2 * filter_pad_1 - filter_size_1) // filter_stride_1 + 1
        HC_1 = (H + 2 * filter_pad_1 - filter_size_1) // filter_stride_1 + 1

        # relu
        # no parameters, no effect on shape of image

        # maxpool_1(3x3)
        # no parameters
        # calculate output shape to use in next layer
        WP_1 = (WC_1 + 2 * pool_pad_1 - pool_size_1) // pool_stride_1 + 1
        HP_1 = (HC_1 + 2 * pool_pad_1 - pool_size_1) // pool_stride_1 + 1

        # conv_3_2(3x3)
        W_conv_3_2 = np.random.normal(loc=0, scale=weight_scale,
                                      size=(channel_1, channel_1, filter_size_1, filter_size_1))
        b_conv_3_2 = np.zeros((channel_1,), dtype=float)

        # calculate output shape to use in next layer
        WC_2 = (WP_1 + 2 * filter_pad_1 - filter_size_1) // filter_stride_1 + 1
        HC_2 = (HP_1 + 2 * filter_pad_1 - filter_size_1) // filter_stride_1 + 1

        # relu
        # no parameters, no effect on image shape

        # maxpool_2(3x3)
        # no parameters
        WP_2 = (WC_2 + 2 * pool_pad_1 - pool_size_1) // pool_stride_1 + 1
        HP_2 = (HC_2 + 2 * pool_pad_1 - pool_size_1) // pool_stride_1 + 1

        # batchnorm2d
        # no effect on image shape
        gamma_bn2d_1 = np.ones((channel_1,))
        beta_bn2d_1 = np.zeros((channel_1,))

        # relu
        # no parameters, no effect on shape of image

        # conv_1_1(1x1)
        W_conv_1_1 = np.random.normal(loc=0.0, scale=weight_scale,
                                      size=(channel_2, channel_1, filter_size_2, filter_size_2))
        b_conv_1_1 = np.zeros((channel_2,), dtype=float)

        # calcualte output shape
        WC_3 = (WP_2 + 2 * filter_pad_2 - filter_size_2) // filter_stride_2 + 1
        HC_3 = (HP_2 + 2 * filter_pad_2 - filter_size_2) // filter_stride_2 + 1

        # maxpool_2(2x2)
        # no parameter
        # Calculate width and height of output of maxpool for affine layer
        WP_3 = (WC_3 + 2 * pool_pad_2 - pool_size_2) // pool_stride_2 + 1
        HP_3 = (HC_3 + 2 * pool_pad_2 - pool_size_2) // pool_stride_2 + 1

        # # affine_1((channel_2 * WP_3 * HP_3) x hidden_dim)
        # W_fc_1 = np.random.normal(loc=0.0, scale=weight_scale,
        #                           size=(channel_2 * WP_3 * HP_3, hidden_dim))
        # b_fc_1 = np.zeros((hidden_dim,), dtype=float)

        # # relu
        # # no effect on image shape

        # # affine_2(hidden_dim x num_classes)
        # W_fc_2 = np.random.normal(loc=0.0, scale=weight_scale,
        #                           size=(hidden_dim, num_classes))
        # b_fc_2 = np.zeros((num_classes,), dtype=float)

        # Debug affine layer:
        W_fc_dbg = np.random.normal(loc=0.0, scale=weight_scale,
                                    size=(channel_2*WP_3*WP_3, num_classes))
        b_fc_dbg = np.zeros((num_classes,), dtype=float)

        # store parameters in self.params
        self.params.update({
            'W_fc_dbg': W_fc_dbg,
            'b_fc_dbg': b_fc_dbg,
            'W_conv_3_1': W_conv_3_1,
            'b_conv_3_1': b_conv_3_1,
            'W_conv_3_2': W_conv_3_2,
            'b_conv_3_2': b_conv_3_2,
            'W_conv_1_1': W_conv_1_1,
            'b_conv_1_1': b_conv_1_1,
            # 'W_fc_1': W_fc_1,
            # 'b_fc_1': b_fc_1,
            # 'W_fc_2': W_fc_2,
            # 'b_fc_2': b_fc_2,
            'gamma_bn2d_1': gamma_bn2d_1,
            'beta_bn2d_1': beta_bn2d_1,
        })

        # convert values in self.params to given dtype
        for k, v in self.params.items():
            self.params[k] = v.astype(dtype)

    def loss(self, X, y=None):
        '''
        Evaluate loss and gradient for the nine-layer convolutional network.

        Inputs:
        - X: Array of input data of shape (N, d_1, ..., d_k).
        - y: Array of labels, of shape (N,). y[i] gives the label for X[i].

        Returns:
        If y is None, then run a test-time forward pass of the model and return:
        - scores: Array of shape (N, C) giving classification scores, where
            scores[i, c] is the classification score for X[i] and class c.

        If y is not None, then run a training-time forward and backward pass and
        return a tuple of:
        - loss: Scalar value giving the loss.
        - grads: Dictionary with the same keys as self.params, mapping parameter
            names to gradients of the loss with respect to those parameters.
        '''
        X = X.astype(self.dtype)
        mode = 'test' if y is None else 'train'

        # extract parameters from self.params
        # W_conv_3_1, b_conv_3_1, W_conv_3_2, b_conv_3_2, W_conv_1_1, b_conv_1_1, \
        #     W_fc_1, b_fc_1, W_fc_2, b_fc_2, gamma_bn2d_1, beta_bn2d_1 = (
        #         self.params[k] for k in self.params.keys())

        # W_conv_3_1, b_conv_3_1, W_conv_3_2, b_conv_3_2, W_conv_1_1, b_conv_1_1, \
        #     W_fc_1, b_fc_1, W_fc_2, b_fc_2, gamma_bn2d_1, beta_bn2d_1 = \
        #     self.params['W_conv_3_1'], self.params['b_conv_3_1'], \
        #     self.params['W_conv_3_2'], self.params['b_conv_3_2'], \
        #     self.params['W_conv_1_1'], self.params['b_conv_1_1'], \
        #     self.params['W_fc_1'], self.params['b_fc_1'], self.params['W_fc_2'], \
        #     self.params['b_fc_2'], self.params['gamma_bn2d_1'], self.params['beta_bn2d_1']

        W_conv_3_1, b_conv_3_1, W_conv_3_2, b_conv_3_2, W_conv_1_1, b_conv_1_1, \
            W_fc_dbg, b_fc_dbg, gamma_bn2d_1, beta_bn2d_1 = \
            self.params['W_conv_3_1'], self.params['b_conv_3_1'], \
            self.params['W_conv_3_2'], self.params['b_conv_3_2'], \
            self.params['W_conv_1_1'], self.params['b_conv_1_1'], \
            self.params['W_fc_dbg'], self.params['b_fc_dbg'], \
            self.params['gamma_bn2d_1'], self.params['beta_bn2d_1']

        # pass conv_param to the forward layer
        # Padding and stride chosen to preserve the input spatial size
        # pad = (filter_size - 1) // 2
        filter_size_1 = self.filter_size_1
        filter_stride_1 = self.filter_stride_1
        filter_pad_1 = self.filter_pad_1

        filter_size_2 = self.filter_size_2
        filter_stride_2 = self.filter_size_2
        filter_pad_2 = self.filter_pad_2

        conv_param_1 = {'stride': filter_stride_1, 'pad': filter_pad_1}
        conv_param_2 = {'stride': filter_stride_2, 'pad': filter_pad_2}

        pool_stride_1 = self.pool_stride_1
        pool_pad_1 = self.pool_pad_1
        pool_size_1 = self.pool_size_1

        pool_stride_2 = self.pool_stride_2
        pool_pad_2 = self.pool_pad_2
        pool_size_2 = self.pool_size_2

        pool_param_1 = {'pool_height': pool_size_1, 'pool_width': pool_size_1,
                        'stride': pool_stride_1}
        pool_param_2 = {'pool_height': pool_size_2, 'pool_width': pool_size_2,
                        'stride': pool_stride_2}

        bn_param = {'mode': 'train'}

        ###############################################################################
        # The implementation of the forward pass for the nine-layer convolutional net.#
        ###############################################################################
        conv_forward = conv_forward_naive
        conv_backward = conv_backward_naive
        max_pool_forward = max_pool_forward_naive
        max_pool_backward = max_pool_backward_naive

        if self.fast == True:
            # Conv2d fast implementation
            conv_forward = conv_forward_strides
            conv_backward = conv_backward_strides

            # Max pooling fast implementation
            max_pool_forward = max_pool_forward_fast
            max_pool_backward = max_pool_backward_fast

        # Sandwich layer 1: conv(3x3) - relu - maxpool(3x3)
        # print('# Sandwich layer 1: conv(3x3) - relu - maxpool(3x3)')
        out_conv_3_1, cache_conv_3_1 = conv_forward(
            X, W_conv_3_1, b_conv_3_1, conv_param_1)
        out_relu_1, cache_relu_1 = relu_forward(out_conv_3_1)
        out_pool_1, cache_pool_1 = max_pool_forward(
            out_relu_1, pool_param_1)

        # Sandwich layer 2: conv(3x3) - relu - maxpool(3x3)
        # print('# Sandwich layer 2: conv(3x3) - relu - maxpool(3x3)')
        out_conv_3_2, cache_conv_3_2 = conv_forward(
            out_pool_1, W_conv_3_2, b_conv_3_2, conv_param_1)
        out_relu_2, cache_relu_2 = relu_forward(out_conv_3_2)
        out_pool_2, cache_pool_2 = max_pool_forward(
            out_relu_2, pool_param_1)

        # Sandwich layer 3: batchnorm2d - relu - conv(1x1) - maxpool(2x2)
        # print('# Sandwich layer 3: batchnorm2d - relu - conv(1x1) - maxpool(2x2)')
        # print(f'gamma_bn2d_1=\n{gamma_bn2d_1}')
        out_bn2d, cache_bn2d = spatial_batchnorm_forward(
            out_pool_2, gamma_bn2d_1, beta_bn2d_1, bn_param)
        out_relu_3, cache_relu_3 = relu_forward(out_bn2d)
        out_conv_1_1, cache_conv_1_1 = conv_forward(
            out_relu_3, W_conv_1_1, b_conv_1_1, conv_param_2)
        out_pool_3, cache_pool_3 = max_pool_forward(
            out_conv_1_1, pool_param_2)

        # # Sandwich layer 4: affine - relu
        # out_fc_1, cache_fc_1 = affine_forward(out_pool_3, W_fc_1, b_fc_1)
        # out_relu_4, cache_relu_4 = relu_forward(out_fc_1)

        # # Sandwich layer 5: affine
        # out_fc_2, cache_fc_2 = affine_forward(out_relu_4, W_fc_2, b_fc_2)

        # Debug affine layer:
        out_fc_2, cache_fc_2 = affine_forward(out_pool_3, W_fc_dbg, b_fc_dbg)

        # final output
        scores = out_fc_2

        # Return scores if mode is test
        if mode == 'test':
            return scores

        #########################################################################################
        # The implementation of the backward pass for the nine-layer convolutional net,         #
        # the loss and gradients will be stored in the loss and grads variables. Data           #
        # loss will be computed using softmax. Grads[k] holds the gradients for self.params[k]. #
        # L2 regularization is used with a factor of 0.5 to simplify the expression for         #
        # the gradient.                                                                         #
        #########################################################################################
        loss, grads = 0, {}
        reg = self.reg

        # Softmax scores
        loss, d_scores = softmax_loss(scores, y)

        # Debug affine layer:
        dout, dW, db = affine_backward(d_scores, cache_fc_2)
        # L2 regularization
        loss += reg * 0.5 * np.sum(W_fc_dbg*W_fc_dbg)
        dW += reg * W_fc_dbg
        grads.update({'W_fc_dbg': dW, 'b_fc_dbg': db})

        # # Sandwich layer 5: affine
        # dout, dW, db = affine_backward(d_scores, cache_fc_2)
        # # # L2 regularization
        # loss += reg * 0.5 * np.sum(W_fc_2*W_fc_2)
        # dW += reg * W_fc_2
        # grads.update({'W_fc_2': dW, 'b_fc_2': db})

        # # Sandwich layer 4: affine - relu
        # dout = relu_backward(dout, cache_relu_4)
        # dout, dW, db = affine_backward(dout, cache_fc_1)
        # # # L2 regularization
        # loss += reg * 0.5 * np.sum(W_fc_1 * W_fc_1)
        # dW += reg * W_fc_1
        # grads.update({'W_fc_1': dW, 'b_fc_1': db})

        # Sandwich layer 3: batchnorm2d - relu - conv(1x1) - maxpool(2x2)
        dout = max_pool_backward(dout, cache_pool_3)
        dout, dW, db = conv_backward(dout, cache_conv_1_1)
        dout = relu_backward(dout, cache_relu_3)
        dout, dgamma, dbeta = spatial_batchnorm_backward(dout, cache_bn2d)
        # # L2 regularization
        loss += reg * 0.5 * np.sum(W_conv_1_1*W_conv_1_1)
        dW += reg * W_conv_1_1
        grads.update({'W_conv_1_1': dW, 'b_conv_1_1': db})
        grads.update({'gamma_bn2d_1': gamma_bn2d_1, 'beta_bn2d_1': beta_bn2d_1})

        assert np.sum(dW) != 0

        # Sandwich layer 2: conv(3x3) - relu - maxpool(3x3)
        dout = max_pool_backward(dout, cache_pool_2)
        dout = relu_backward(dout, cache_relu_2)
        dout, dW, db = conv_backward(dout, cache_conv_3_2)
        # # L2 regularization
        loss += reg * 0.5 * np.sum(W_conv_3_2*W_conv_3_2)
        dW += reg * W_conv_3_2
        grads.update({'W_conv_3_2': dW, 'b_conv_3_2': db})

        assert np.sum(dW) != 0

        # Sandwich layer 1: conv(3x3) - relu - maxpool(3x3)
        dout = max_pool_backward(dout, cache_pool_1)
        dout = relu_backward(dout, cache_relu_1)
        dout, dW, db = conv_backward(dout, cache_conv_3_1)
        # # L2 regularization
        loss += reg * 0.5 * np.sum(W_conv_3_1*W_conv_3_1)
        dW += reg * W_conv_3_1
        grads.update({'W_conv_3_1': dW, 'b_conv_3_1': db})

        assert np.sum(dW) != 0

        return loss, grads
