import numpy as np
# import cupy as cp

try:
    from im2col_cython import col2im_cython, im2col_cython
    from im2col_cython import col2im_6d_cython
except ImportError:
    print('The message below can be safely ignored if fast implementation of Conv2d and MaxPool is not used.')
    print('\tIt is needed to compile a Cython extension for a portion of this net.')

from im2col import *

# TODO: Fast Implementation of Convolution and Maxpooling Layers


def conv_forward_strides(x, w, b, conv_param):
    '''
    Fast implementation of the forward pass for a convolutional layer.

    Input / Output: The same as those used in forward pass of naive
    convolutinal layer.
    '''
    N, C, H, W = x.shape
    F, _, HH, WW = w.shape
    stride, pad = conv_param['stride'], conv_param['pad']

    # # Check dimensions
    assert (W + 2 * pad - WW) % stride == 0, 'width does not work'
    assert (H + 2 * pad - HH) % stride == 0, 'height does not work'

    # pad the input
    p = pad
    x_padded = np.pad(x, ((0, 0), (0, 0), (p, p), (p, p)), mode='constant',
                      constant_values=((0, 0), (0, 0), (0, 0), (0, 0)))

    # Figure out output dimensions
    H += 2 * pad
    W += 2 * pad
    out_h = (H - HH) // stride + 1
    out_w = (W - WW) // stride + 1

    # Perform an im2col operation by picking clever strides
    shape = (C, HH, WW, N, out_h, out_w)
    strides = (H * W, W, 1, C * H * W, stride * W, stride)
    strides = x.itemsize * np.array(strides)
    x_stride = np.lib.stride_tricks.as_strided(
        x_padded, shape=shape, strides=strides)
    x_cols = np.ascontiguousarray(x_stride)
    x_cols.shape = (C*HH*WW, N*out_h*out_w)

    # Now all our convolutions are a big matrix multiply
    res = w.reshape(F, -1).dot(x_cols) + b.reshape(-1, 1)

    # Reshape the output
    res.shape = (F, N, out_h, out_w)
    out = res.transpose(1, 0, 2, 3)

    # Be nice and return a contiguous array
    out = np.ascontiguousarray(out)

    cache = (x, w, b, conv_param, x_cols)
    return out, cache


def conv_backward_strides(dout, cache):
    '''
    Fast implementation of the backward pass for a convolutinal layer.

    Input / Output: The same as those used in backward pass of naive
    convolutional layer
    '''
    x, w, b, conv_param, x_cols = cache
    stride, pad = conv_param['stride'], conv_param['pad']

    N, C, H, W = x.shape
    F, _, HH, WW = w.shape
    _, _, out_h, out_w = dout.shape

    db = np.sum(dout, axis=(0, 2, 3))

    dout_reshaped = dout.transpose(1, 0, 2, 3).reshape(F, -1)
    dw = dout_reshaped.dot(x_cols.T).reshape(w.shape)

    dx_cols = w.reshape(F, -1).T.dot(dout_reshaped)
    dx_cols.shape = (C, HH, WW, N, out_h, out_w)
    dx = col2im_6d_cython(dx_cols, N, C, H, W, HH, WW, pad, stride)

    return dx, dw, db


def max_pool_forward_reshape(x, pool_param):
    '''
    A fast implementation of the forward pass for the max pooling layer
    that uses some clever reshaping.

    This can only be used for square pooling regions that tile the input.
    '''
    N, C, H, W = x.shape
    pool_height, pool_width, stride = pool_param['pool_height'], \
        pool_param['pool_width'], pool_param['stride']

    assert pool_height == pool_width == stride, 'Invalid pool params'
    assert H % pool_height == 0
    assert W % pool_height == 0  # height and width are equal
    x_reshaped = x.reshape(
        N, C, H // pool_height, pool_height, W // pool_width, pool_width
    )
    out = x_reshaped.max(axis=3).max(axis=4)

    cache = (x, x_reshaped, out)
    return out, cache


def max_pool_backward_reshape(dout, cache):
    '''
    A fast implementation of the backward pass for the max pooling layer that
    uses some clever broadcasting and reshaping.

    This can only be used if the forward pass was computed using
    max_pool_forward_reshape.

    NOTE: If there are multiple argmaxes, this method will assign gradient to
    **ALL** argmax elements of the input rather than picking one. In this case
    the gradient will actually be incorrect. However this is unlikely to ovvur
    in practice, so it shouldn't matter much. One possible solution is to split
    the upstream gradient equally among all argmax elements; this should result
    in a valid subtradient. you can make this happen by uncommenting the line
    below; however this results in a significant performance penalty (about
    40% lower) and is unlikely to matter in practice so we don't do that.
    '''
    x, x_reshaped, out = cache

    dx_reshaped = np.zeros(x_reshaped.shape)
    out_newaxis = out[:, :, :, np.newaxis, :, np.newaxis]
    mask = x_reshaped == out_newaxis
    dout_newaxis = dout[:, :, :, np.newaxis, :, np.newaxis]
    dout_broadcast, _ = np.broadcast_arrays(dout_newaxis, dx_reshaped)
    dx_reshaped[mask] = dout_broadcast[mask]
    dx_reshaped /= np.sum(mask, axis=(3, 5), keepdims=True)
    dx = dx_reshaped.reshape(x.shape)

    return dx


def max_pool_forward_fast(x, pool_param):
    '''
    A fast implementation of the forward pass for a max pooling layer.

    This chooses between the reshape method and the im2col method. If
    the pooling regions are square and tile the input image, then we can
    use the reshape method which is very fast. Otherwise we fall back on
    the naive method.
    '''
    N, C, H, W = x.shape
    pool_height, pool_width = pool_param['pool_height'], pool_param['pool_width']
    stride = pool_param['stride']

    same_size = pool_height == pool_width == stride
    tiles = H % pool_height == 0 and W % pool_width == 0
    if same_size and tiles:
        out, reshape_cache = max_pool_forward_reshape(x, pool_param)
        cache = ('reshape', reshape_cache)
    else:
        out, naive_cache = max_pool_forward_naive(x, pool_param)
        cache = ('naive', naive_cache)

    return out, cache


def max_pool_backward_fast(dout, cache):
    '''
    A fast implementation of the backward pass for a max pooling layer.

    This switches between the reshape method and the naive method
    depending on which method was used to generate the cache.
    '''
    method, real_cache = cache
    if method == 'reshape':
        return max_pool_backward_reshape(dout, real_cache)
    elif method == 'naive':
        return max_pool_backward_naive(dout, real_cache)
    else:
        raise ValueError('Unrecognized method "%s"' % method)


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
    dx = dpadded_x[:, :, pad:pad+H, pad:pad+W]
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
        pool_param.get('pool_width'), pool_param.get('stride', 1), \
        pool_param.get('pad', 0)

    # print(pool_height, pool_width, stride, pad, pool_param)

    HH = pool_height
    WW = pool_width

    # output shape
    H_ = (H + 2 * pad - pool_height) // stride + 1
    W_ = (W + 2 * pad - pool_width) // stride + 1
    # print(f'H_: ({H_}={H}+2*{pad}-{pool_height})//{stride}+1')

    # out = np.zeros((N, C, H_, W_))
    out = np.ones((N, C, H_, W_))
    # print(f'(N,C,H_,W_)=\n{(N,C,H_,W_)}')
    # print(f'initial out=\n{out}')
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
    # print(f'padded_out=\n{padded_out}')
    out = padded_out[:, :, pad:pad+H_, pad:pad+W_]
    # print(f'x=\n{x}\nout={out}')
    # store cache for backprop
    cache = (x, pool_param)
    # print(f'out.shape={out.shape}')

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
    dx = padded_dx[:, :, pad:pad+H, pad:pad+W]

    return dx


def batchnorm_forward(x, gamma, beta, bn_param):
    '''
    Forward pass for batch normalization.

    During training we also keep an exponentially decaying running mean of the
    mean and variance of each feature, and these averages are used to normalize
    data at test-time.

    At each timestep we update the running averages for mean and variances using
    an exponential decay based on the momentum parameter:

    running_mean = momentum * running_mean + (1 - momentum) * sample_mean
    running_var = momentun * running_var + (1 - momentum) * sample_var

    Note that this is different from the test-time behavior suggested by the bach
    normalization pater: they compute sample mean and variance for each feature
    using a large number of training images rather than using a running average.
    For this implementation we have chosen to use running averages instead since 
    they do not require an additional estimation step; the torch7 implementation
    of batch normalization also uses running averages.

    Inputs:
    - x: Data of shape (N, D)
    - gamma: Scale parameter of shape (D,)
    - beta: Shift parameter of shape (D,)
    - bn_param: Dictionary with the following keys:
        - mode: 'train' or 'test'; required
        - eps: Constant for numeric stability
        - momentum: Constant for running mean / variance.
        - running_mean: Array of shape (D,) giving running mean of features
        - running_var: Array of shape (D,) giving running variance of features

    Returns a tuple of:
    - out: of shape (N, D)
    - cache: A tuple of values needed in the backward pass
    '''
    # extract parameters
    mode = bn_param['mode']
    eps = bn_param.get('eps', 1e-5)
    momentum = bn_param.get('momentum', 0.9)

    N, D = x.shape
    running_mean = bn_param.get('running_mean', np.zeros(D, dtype=x.dtype))
    running_var = bn_param.get('running_var', np.zeros(D, dtype=x.dtype))

    out, cache = None, None
    # calculate out for forward pass in training mode
    if mode == 'train':
        mean = np.mean(x, axis=0)
        x_minus_mean = x - mean
        x_minus_mean_sq = x_minus_mean**2
        var = np.sum(x_minus_mean_sq, axis=0) / N
        std_var = np.sqrt(var + eps)
        inv_std_var = 1/std_var
        x_norm = x_minus_mean * inv_std_var
        scaled_x = gamma * x_norm
        out = scaled_x + beta

        # save to cache for backward pass
        cache = {'mean': mean, 'x_minus_mean': x_minus_mean,
                 'x_minus_mean_sq': x_minus_mean_sq,
                 'var': var, 'std_var': std_var,
                 'inv_std_var': inv_std_var, 'x_norm': x_norm,
                 'scaled_x': scaled_x, 'shifted_scaled_x': out,
                 'x': x, 'gamma': gamma, 'beta': beta, 'eps': eps}

        # update running_mean and running_var
        sample_mean = np.mean(x, axis=0)
        sample_var = np.var(x, axis=0)
        running_mean = momentum * running_mean + (1 - momentum) * sample_mean
        running_var = momentum * running_var + (1 - momentum) * sample_var
        # store the updated running means back into bn_param
        bn_param.update({'running_mean': running_mean})
        bn_param.update({'running_var': running_var})

    # calculate out for forward pass in testing mode with running_mean and
    # running_var calculated in training mode
    elif mode == 'test':
        out = (x - running_mean) / (np.sqrt(running_var + eps))
        out = gamma * out + beta

    else:
        raise ValueError('Invalid forward batchnorm mode "%s"' % mode)

    return out, cache


def batchnorm_backward(dout, cache):
    '''
    Backward pass for batch normalization

    Inputs:
    - dout: upstream derivatives, of shape (N, D)
    - cache: Variable of intermediates from batchnorm_forward

    Returns a tuple of:
    - dx: Gradient with respect to inputs x, of shape (N, D)
    - dgamma: Gradient with respect to scale parameter gamma, of shape (D,)
    - dbeta: Gradient with respect to shift parameter beta, of shape (D,)
    '''
    dx, dgamma, dbeta = None, None, None

    # extract parameters
    N, D = dout.shape
    mean, x_minus_mean, x_minus_mean_sq, var, std_var, inv_std_var, \
        x_norm, scaled_x, shifted_scaled_x, x, gamma, beta, eps = \
        cache['mean'], cache['x_minus_mean'], cache['x_minus_mean_sq'], \
        cache['var'], cache['std_var'], cache['inv_std_var'], \
        cache['x_norm'], cache['scaled_x'], cache['shifted_scaled_x'], \
        cache['x'], cache['gamma'], cache['beta'], cache['eps']

    # calculate backward pass for batch normalization
    dgamma = np.sum(x_norm * dout, axis=0)
    dbeta = np.sum(dout, axis=0)
    dx_hat = dout * gamma  # also named dx_norm
    dinv_std_var = np.sum(dx_hat * x_minus_mean, axis=0)
    dx_minus_mean = dx_hat * inv_std_var
    dstd_var = dinv_std_var * -1/(std_var**2)
    # can be replaced with inv_std_var ?
    dvar = dstd_var * (1/2) * 1/np.sqrt(var+eps)
    dx_minus_mean_sq = dvar * np.ones((N, D)) / N
    dx_minus_mean += dx_minus_mean_sq * 2 * x_minus_mean
    dmean = np.sum(dx_minus_mean * np.ones((N, D)), axis=0) * (-1)
    dx = dx_minus_mean
    dx += dmean * np.ones((N, D)) / N

    return dx, dgamma, dbeta


def spatial_batchnorm_forward(x, gamma, beta, bn_param):
    '''
    Computes the forward pass for spatial batch normalization, which is
    also named batchnorm2d.

    Inputs:
    - x: Input data of shape (N, C, H, W)
    - gamma: Scale parameter, of shape (C,)
    - beta: Shift parameter, of shape (C,)
    - bn_param: Dictionary with the following keys:
        - mode: 'train' or 'test'
        required
        - eps: Constant for numeric stability
        - momentum: Constant for running mean / variance. momentum = 0 means that
        out information is discarded completely at every time step, while
        momentum = 1 means that new information is never incorporated. The
        default of momentum = 0.9.
        - running_mean: Array of shape (D,) giving running mean of features
        - running_var: Array of shape (D,) giving running variance of features

    Returns a tuple of:
    - out: Output data, of shape (N, C, H, W)
    - cache: Values needed for the backward pass
    '''

    out, cache = None, None
    N, C, H, W = x.shape
    # transpose x to treat N, H and W equally in the batchnormazation
    # for the reason that every feature channel is produced by the same
    # convolutional filter
    x_T = x.transpose((0, 2, 3, 1)).reshape((N*H*W, C))
    out, cache = batchnorm_forward(x_T, gamma, beta, bn_param)
    # transpose and reshape back to shape (N, C, H, W)
    out = out.reshape((N, H, W, C)).transpose((0, 3, 1, 2))

    return out, cache


def spatial_batchnorm_backward(dout, cache):
    '''
    Conputes the backward pass for spatial batch normalization.

    Inputs:
    - dout: Upstream derivatives, of shape (N, C, H, W)
    - cache: Values from the forward pass

    Returns a tuple of:
    - dx: Gradient with respect to inputs, of shape (N, C, H, W)
    - dgamma: Gradient with respect to scale parameter, of shape (C,)
    - dbeta: Gradient with respect to shift parameter, of shape (C,)
    '''
    dx, dgamma, dbeta = None, None, None
    N, C, H, W = dout.shape
    # same preprocess as in forward pass for the same reason
    dout_T = dout.transpose((0, 2, 3, 1)).reshape((N*H*W, C))
    dx, dgamma, dbeta = batchnorm_backward(dout_T, cache)
    # reshape and transpose dx back  to shape (N, C, H, W)
    dx = dx.reshape((N, H, W, C)).transpose((0, 3, 1, 2))

    return dx, dgamma, dbeta


def affine_forward(x, w, b):
    '''
    Conputes the forward pass for an affine (fully-connected) layer.

    The input x has shape (N, d_1, ..., d_k) and contains a minibatch of N
    examples, where each example x[i] has shape (d_1, ..., d_k). We will
    reshape each input into a vector of dimension D = d_1 * ... * d_k, and
    then transform it to an output vector of dimension M.

    Inputs:
    - x: A numpy array containing input data, of shape (N, d_1, ..., d_k)
    - w: A numpy array of weights, of shape (D, M)
    - b: A numpy array of biases, of shape (M,)

    Returns a tuple of:
    - out: Output, of shape (N, M)
    - cache: (x, w, b)
    '''
    out = None
    N = x.shape[0]
    D = w.shape[0]
    # calculate out
    out = x.reshape(N, D).dot(w) + b[np.newaxis, :]
    # store cache for backward pass
    cache = (x, w, b)

    return out, cache


def affine_backward(dout, cache):
    '''
    Computes the backward pass for an affine layer.

    Inputs:
    - dout:
    Upstream derivative, of shape (N, M)
    - cache: Tuple of:
        - x: Input data, of shape (N, d_1, ..., d_k)
        - w: Weights, of shape (D, M)
        - b: Biases, of shape (M,)

    Returns a tuple of:
    - dx: Gradient with respect to x, of shape (N, d_1, ..., d_k)
    - dw: Gradient with respect to w, of shape (D, M)
    - db: Gradient with respect to b, of shape (M,)
    '''
    # extract parameters
    x, w, b = cache
    dx, dw, db = None, None, None
    N = x.shape[0]
    D = w.shape[0]
    # calculate backward pass
    # db = np.sum(dout.transpose(), axis=1)
    # upper db expression is equal to below
    db = np.sum(dout, axis=0)
    dw = x.reshape(N, D).transpose().dot(dout)
    dx = dout.dot(w.transpose()).reshape(x.shape)

    return dx, dw, db


def relu_forward(x):
    '''
    Conputes the forward pass for a layer of rectified linear units (ReLUs).

    Input:
    - x: Inputs, of any shape

    Returns a tuple of:
    - out: Output, of the same shape as x
    - cache: x, to be used in backward pass
    '''
    out = np.maximum(0, x)
    cache = x
    return out, cache


def relu_backward(dout, cache):
    '''
    Computes the backward pass for a layer of rectified linear units (ReLUs).

    Input:
    - dout: Upstream derivatives, of any shape
    - cache: Input x, of same shape as dout

    Returns:
    - dx: Gradient with respect
    '''
    dx, x = None, cache
    binary = np.zeros(x.shape)
    binary[x >= 0] = 1
    dx = binary * dout

    return dx


def softmax_loss(x, y):
    '''
    Computes the loss and gradient for softmax classification.

    Inputs:
    - x: Input data, of shape (N, C) where x[i, j] is the score for the jth
    class for  the ith input.
    - y: Vector of labels, of shape (N,) where y[i] is the label for x[i] and
    0 <= y[i] < C

    Returns a tuple of:
    - loss: Scalar giving the loss
    - dx: Gradient of the loss with respect to x
    '''
    loss, dx = None, None
    num_train, num_classed = x.shape

    # calculate loss
    scores = x
    X_index = np.arange(num_train)
    Xi_Wyi = scores[X_index, y]
    sum_Xi_Wyi = np.sum(Xi_Wyi)
    exp_scores = np.exp(scores)
    sum_axis_1_exp_scores = np.sum(exp_scores, axis=1)
    log_sum_axis_1_exp_scores = np.log(sum_axis_1_exp_scores)
    sum_log_sum_axis_1_exp_scores = np.sum(log_sum_axis_1_exp_scores)
    loss = (sum_log_sum_axis_1_exp_scores - sum_Xi_Wyi) / num_train

    # calculate gradient with respect to x
    df = exp_scores
    df /= sum_axis_1_exp_scores[:, np.newaxis]
    df[X_index, y] += -1
    dx = df / num_train

    return loss, dx
