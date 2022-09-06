from builtins import range
from tkinter.tix import X_REGION
from xml.etree.ElementInclude import XINCLUDE_INCLUDE
import numpy as np
from random import shuffle
from past.builtins import xrange


def softmax_loss_naive(W, X, y, reg):
    """
    Softmax loss function, naive implementation (with loops)

    Inputs have dimension D, there are C classes, and we operate on minibatches
    of N examples.

    Inputs:
    - W: A numpy array of shape (D, C) containing weights.
    - X: A numpy array of shape (N, D) containing a minibatch of data.
    - y: A numpy array of shape (N,) containing training labels; y[i] = c means
      that X[i] has label c, where 0 <= c < C.
    - reg: (float) regularization strength

    Returns a tuple of:
    - loss as single float
    - gradient with respect to weights W; an array of same shape as W
    """
    # Initialize the loss and gradient to zero.
    loss = 0.0
    dW = np.zeros_like(W)

    #############################################################################
    # TODO: Compute the softmax loss and its gradient using explicit loops.     #
    # Store the loss in loss and the gradient in dW. If you are not careful     #
    # here, it is easy to run into numeric instability. Don't forget the        #
    # regularization!                                                           #
    #############################################################################
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    num_train = X.shape[0]
    # print(f'num_train={num_train}')
    num_classes = W.shape[1]
    for i in range(num_train):
        scores = X[i].dot(W)  # scores[1,C]
        exp_scores = np.exp(scores)
        sum_exp = np.sum(exp_scores)
        log_sum_exp = np.log(sum_exp)
        loss += log_sum_exp - scores[y[i]]
        # X_T = X.transpose()
        for j in range(num_classes):
            if(j == y[i]):
                dW[:, j] += (exp_scores[j]/sum_exp-1)*X[i].transpose()
            else:
                dW[:, j] += exp_scores[j]/sum_exp*X[i].transpose()

    loss /= num_train
    loss += reg * np.sum(W*W)

    dW /= num_train
    dW += 2*reg*W

    # . # # # . # # # # #
    # . # . # . # . # . #
    # . # # # . # # # # #

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return loss, dW


def softmax_loss_vectorized(W, X, y, reg):
    """
    Softmax loss function, vectorized version.

    Inputs and outputs are the same as softmax_loss_naive.
    """
    # Initialize the loss and gradient to zero.
    loss = 0.0
    dW = np.zeros_like(W)

    #############################################################################
    # TODO: Compute the softmax loss and its gradient using no explicit loops.  #
    # Store the loss in loss and the gradient in dW. If you are not careful     #
    # here, it is easy to run into numeric instability. Don't forget the        #
    # regularization!                                                           #
    #############################################################################
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # loss part
    num_train = X.shape[0]
    num_classes = W.shape[1]
    scores = X.dot(W)
    X_index = np.arange(num_train)
    Xi_Wyi = scores[X_index, y]  # to be subtracted
    sum_Xi_Wyi = np.sum(Xi_Wyi)
    # print(f'Xi_Wyi.shape={Xi_Wyi.shape}')

    exp_scores = np.exp(scores)
    sum_axis_1_exp_scores = np.sum(exp_scores, axis=1)
    # print(f'sum_axis_1_exp_scores.shape={sum_axis_1_exp_scores.shape}')
    log_sum_axis_1_exp_scores = np.log(sum_axis_1_exp_scores)
    sum_log_sum_axis_1_exp_scores = np.sum(log_sum_axis_1_exp_scores)
    # print(
    #     f'sum_log_sum_axis_1_exp_scores.shape={sum_log_sum_axis_1_exp_scores.shape}')

    # regularization
    loss = sum_log_sum_axis_1_exp_scores - sum_Xi_Wyi

    loss /= num_train
    loss += reg*np.sum(W*W)
    # print(f'loss.shape={loss.shape}')

    # gradient part
    margins = exp_scores/sum_axis_1_exp_scores[:, np.newaxis]
    # should be NxC
    # print(f'margins.shape={margins.shape}')
    margins[X_index, y] -= 1
    X_T = X.transpose()
    dW = X_T.dot(margins)

    # regularization
    dW /= num_train
    dW += 2*reg*W

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return loss, dW
