import numpy as np

'''
This file implements some first-order update rules that are commonly used
for training neural networks: SGD, Adam. Each update rule has the same
interface:

def update(w, dw, config=None):

Inputs:
- w: A numpy array giving the current weights.
- dw: A numpy array of the same shape as w giving the gradient of the loss
    with respect to w.
- config: A dictionary containing hyperparameter values such as learning
    rate, momentum, etc. If the update rule requires caching values over
    many iterations, then config will also hold these cached values.

Returns:
- next_w: The next w point after the update.
- config: The config dictionary to be passed to the next iteration of the
    update rule.
'''

def sgd(w, dw, config=None):
    '''
    Perform vanilla stochastic gradient desent.

    consig format:
    - learning_rate: Scalar learning rate.
    '''
    if config is None:
        config = {}
    config.setdefault('learning_rate', 1e-2)

    w -= config['learning_rate'] * dw
    return w, config

def adam(w, dw, config=None):
    '''
    Uses the Adam update rule, which incorporates moving averages of both the
    gradients and its square and a bias correction term.

    config format:
    - learning_rate: Scalar learning rate.
    - beta1: Decay rate for moving average of first moment of gradient.
    - beta2: Decay rate for moving average of second moment of gradient.
    - epsilon: Small scalar used for smoothing to avoid numerical error: 
        dividing by zero.
    - m: Moving average of gradient.
    - v: Moving average of squared gradient.
    - t: Iteration number.
    '''
    if config is None:
        config = {}
    config.setdefault('learning_rate', 1e-3)
    config.setdefault('beta1', 0.9)
    config.setdefault('beta2', 0.999)
    config.setdefault('epsilon', 1e-8)
    config.setdefault('m', np.zeros(w.shape))
    config.setdefault('v', np.zeros(w.shape))
    config.setdefault('t', 0)

    next_w = None

    # Implementation of the Adam update formula
    # NOTE: t is modified _before_ using it in any calculations to
    # reference output.

    # Extract parameters from config
    learning_rate = config['learning_rate']
    beta1 = config['beta1']
    beta2 = config['beta2']
    eps = config['epsilon']
    m = config['m']
    v = config['v']
    t = config['t']

    # Update t to sync with iteration
    t += 1

    m = beta1 * m + (1 - beta1) * dw
    v = beta2 * v + (1 - beta2) * (dw**2)
    mt = m / (1 - beta1**t)
    vt = v / (1-beta2**t)
    next_w = w - learning_rate * mt / (np.sqrt(vt) + eps)

    # Update parameters in config
    config['m'] = m
    config['v'] = v
    config['t'] = t

    return next_w, config