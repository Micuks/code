import numpy as np


def eval_numerical_gradient_array(f, x, df, h=1e-5):
    '''
    Evaluate a numeric gradient for a function that acceps a numpy array and
    returns a numpy array.
    '''
    grad = np.zeros(x.shape)
    # multi-dimension iterator
    it = np.nditer(x, flags=['multi_index'], op_flags=['readwrite'])
    while not it.finished:
        ix = it.multi_index

        oldval = x[ix]
        x[ix] = oldval+h
        pos = f(x).copy()
        x[ix] = oldval-h
        neg = f(x).copy()
        x[ix] = oldval

        grad[ix] = np.sum((pos-neg)*df)/(2*h)
        it.iternext()

    return grad


def eval_numerical_gradient(f, x, verbose=True, h=1e-5):
    '''
    A naive implementation of numerical gradient of f at x
    - f should be a function that takes a single argument
    - x is the point (numpy array) to evaluate the gradient at
    '''
    fx = f(x)  # evaluate function value at original point
    grad = np.zeros(x.shape)
    # iterate over all indexes in x
    it = np.nditer(x, flags=['multi_index'], op_flags=['readwrite'])
    while not it.finished:
        # evaluate function at x+h
        ix = it.multi_index
        oldval = x[ix]
        x[ix] = oldval + h  # increment by h
        fxph = f(x)  # evaluate f(x + h)
        x[ix] = oldval - h  # decrement by h
        fxmh = f(x)  # evaluate f(x - h)
        x[ix] = oldval  # restore x[ix]

        # compute the partial derivative with centered formula
        grad[ix] = (fxph - fxmh) / (2 * h)  # the slope
        if verbose:
            print(ix, grad[ix])
        it.iternext()  # step to next dimension

    return grad
