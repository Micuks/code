import numpy as np
from MyConvNet import *
def MyConvNetSanityCheckLoss():
    '''
    Sanity check the loss. For softmax loss is used, it is expected
    that the loss for random weights (and no regularization) to be
    about log(C) for C classes. When regularization is used, the loss
    should go up slightly.
    '''
    model = MyConvNet()
    
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

if __name__ == '__main__':
    '''
    Can be executed directly for debug conveniently
    '''
    MyConvNetSanityCheckLoss()