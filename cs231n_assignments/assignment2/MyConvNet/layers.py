import numpy as np


# TODO: Fast Implementation of Convolution and Maxpooling Layers


def conv_forward_naive(x, w, b, conv_param):
    '''
    A naive implementation of the forward pass for a convolutional layer

    Input:
    - x: Input data of shape (N, C, H, W)
    - w: Filter weights of shape (F, C, HH, WW)
    - b: Biases, of shape (F,)
    - conv_param: A dictionary with the following keys:
        - 'stride': The number of pixels between adjacent receptive fields
            in the horizontal and vertical directions.
        - 'pad': The number of pixels that will be used to zero-pad the input.

    Returns a tuple of:
    - out: Output data, of shape (N, F, H_, W_), where H_ and W_ are given by
        H_ = (H + 2 * pad - HH) / stride + 1
        W_ = (W + 2 * pad - WW) / stride + 1
    - cache: (x, w, b, conv_param)
    '''

    out = None

    # The implementation of convolutional forward pass.
    stride, pad = conv_param['stride'], conv_param['pad']
    N, C, H, W = x.shape
    F, C, HH, WW = w.shape
    # add padding to the input
    padded_x = np.pad(x, ((0, 0), (0, 0), (pad, pad), (pad, pad)),
                      'constant', constant_values=((0, 0), (0, 0), (0, 0), (0, 0)))

    H_ = (H+2*pad-HH)//stride+1
    W_ = (W+2*pad-WW)//stride+1

    # implement naive forward pass
    out = np.zeros((N, F, H_, W_))
    for iter_n in range(N):
        for iter_f in range(F):
            for iter_h in range(H_):
                for iter_w in range(W_):
                    h_begin = iter_h*stride
                    h_end = h_begin+HH
                    w_begin = iter_w*stride
                    w_end = w_begin+WW
                    out[iter_n, iter_f, iter_h, iter_w] = np.sum(
                        padded_x[iter_n, :, h_begin:h_end, w_begin:w_end]
                        * w[iter_f, :]) + b[iter_f]

    cache = (x, w, b, conv_param)

    return out, cache


def conv_backward_naive(dout, cache):
    '''
    A naive implementation of the backward pass for a convolutional layer.

    Inputs:
    - dout: Upstream derivatives.
    - cache: A tuple of shape (x, w, b, conv_param) as in conv_forward_naive

    Returns a tuple of:
    - dx: Gradient with respect to x
    - dw: Gradient with respect to w
    - db: Gradient with respect to b
    '''

    dx, dw, db = None, None, None

    # Naive implementation of backward pass
    x, w, b, conv_param = cache
    N, C, H, W = x.shape
    F, C, HH, WW = w.shape
    stride, pad = conv_param['stride'], conv_param['pad']

    H_ = (H+2*pad-HH)//stride+1
    W_ = (W+2*pad-WW)//stride+1

    padded_x = np.pad(x, ((0, 0), (0, 0), (pad, pad), (pad, pad)), 'constant')

    dx = np.zeros(x.shape)
    dw = np.zeros(w.shape)
    db = np.zeros(b.shape)
    dpadded_x = np.zeros(padded_x.shape)

    # calculate convolution backprop
    for iter_n in range(N):
        for iter_f in range(F):
            db[iter_f] += np.sum(dout[iter_n, iter_f, :, :])
            for iter_h in range(H_):
                for iter_w in range(W_):
                    h_begin = iter_h*stride
                    h_end = h_begin+HH
                    w_begin = iter_w*stride
                    w_end = w_begin+WW
                    # filter convolutes with all channels of x
                    dpadded_x[iter_n, :, h_begin:h_end, w_begin:w_end] \
                        += dout[iter_n, iter_f, iter_h, iter_w] * w[iter_f]
                    dw[iter_f, :] += dout[iter_n, iter_f, iter_h, iter_w] \
                        * padded_x[iter_n, :, h_begin:h_end, w_begin:w_end]

    # delete padding zone
    dx = dpadded_x[:, :, pad:-pad, pad:-pad]
    # check shape
    assert dx.shape == x.shape

    return dx, dw, db


def max_pool_forward_naive(x, pool_param):
    '''
    A naive implementation of the forward pass for a max-pooling layer.

    Inputs:
    - x: Input data, of shape (N, C, H, W)
    - pool_param:
    dictionary with the following keys:
        - 'pool_height': The height of each pooling region
        - 'pool_width': The width of each pooling region
        - 'stride': The distance between adjacent pooling regions
        - 'pad': The number of pixels that will be used to zero-pad the input

    Returns a tuple of:
    - out: Output data, of shape (N, C, H_, W_) where H_ and W_ are given by
    H_ = (H + 2 * pad - pool_height) / stride
    W_ = (W + 2 * pad - pool_height) / stride
    - cache: (x, pool_param)
    '''
    out = None

    # extract parameters
    N, C, H, W = x.shape
    pool_height, pool_width, stride, pad = pool_param.get('pool_height'), \
        pool_param.get('pool_width'), pool_param(
            'stride', 1), pool_param('pad', 0)

    HH = pool_height
    WW = pool_width

    # output shape
    H_ = (H + 2 * pad - pool_height) // stride + 1
    W_ = (W + 2 * pad - pool_height) // stride + 1

    out = np.zeros((N, C, H_, W_))
    # add padding to out and x
    padded_out = np.pad(out, ((0, 0), (0, 0), (pad, pad), (pad, pad)),
                        'constant', constant_values=((0, 0), (0, 0), (0, 0), (0, 0)))
    padded_x = np.pad(x, ((0, 0), (0, 0), (pad, pad), (pad, pad)),
                      'constant', constant_values=((0, 0), (0, 0), (0, 0), (0, 0)))

    # calculate the forward pass
    for iter_n in range(N):
        for iter_c in range(C):  # can be optimized to vector calculate on dimension C
            for iter_h in range(H_):
                for iter_w in range(W_):
                    h_begin = iter_h*stride
                    h_end = h_begin+HH
                    w_begin = iter_w*stride
                    w_end = w_begin+WW
                    padded_out[iter_n, iter_c, iter_h, iter_w] = np.amax(
                        padded_x[iter_n, iter_c, h_begin:h_end, w_begin:w_end], axis=(0, 1))

    # delete padding from out
    out = padded_out[:, :, pad:-pad, pad:-pad]
    # store cache for backprop
    cache = (x, pool_param)

    return out, cache


def max_pool_backward_naive(dout, cache):
    '''
    A naive implementation of the backward pass for a max-pooling layer.

    Inputs:
    - dout: Upstream derivatives
    - cache: A tuple of shape (x, pool_param) as in the forward pass.

    Returns:
    - dx: Gradient with respect to x (with the same shape as x)
    '''
    dx = None

    # extract cache
    x, pool_param = cache
    pool_height, pool_width, stride, pad = pool_param.get('pool_height'), \
        pool_param.get('pool_width'), pool_param.get('stride', 1), \
        pool_param.get('pad', 0)

    # alias for pool_height and pool_width
    HH, WW = pool_height, pool_width

    N, C, H, W = x.shape

    # calculate H_ and W_( with padding)
    H_ = (H+2*pad-pool_height)//stride + 1
    W_ = (W+2*pad-pool_width)//stride + 1

    dx = np.zeros(x.shape)
    # add padding to dout, dx and x
    padded_dout = np.pad(dout, ((0, 0), (0, 0), (pad, pad), (pad, pad)),
                         'constant', constant_values=((0, 0), (0, 0), (0, 0), (0, 0)))
    padded_x = np.pad(x, ((0, 0), (0, 0), (pad, pad), (pad, pad)),
                      'constant', constant_values=((0, 0), (0, 0), (0, 0), (0, 0)))
    padded_dx = np.pad(dx, ((0, 0), (0, 0), (pad, pad), (pad, pad)),
                       'constant', constant_values=((0, 0), (0, 0), (0, 0), (0, 0)))

    # calculate backward pass for max-pooling
    for iter_n in range(N):
        for iter_c in range(C):
            for iter_h in range(H_):
                for iter_w in range(W_):
                    h_begin = iter_h*stride
                    h_end = h_begin+HH
                    w_begin = iter_w*stride
                    w_end = w_begin+WW
                    idx_max_val = np.argmax(
                        padded_x[iter_n, iter_c, h_begin:h_end, w_begin:w_end])
                    # reshape index of max value to filter's shape
                    idx_unravel = np.unravel_index(
                        idx_max_val, padded_x[iter_n, iter_c, h_begin:h_end, w_begin:w_end].shape)
                    padded_dx[iter_n, iter_c, h_begin:h_end, w_begin:w_end][idx_unravel] = \
                        padded_dout[iter_n, iter_c, iter_h, iter_w]

    # remove padding from dx
    dx = padded_dx[:, :, pad:-pad, pad:-pad]

    return dx

    # calculate the max pooling backward pass
