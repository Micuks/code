from builtins import range
from multiprocessing.context import ForkContext
from textwrap import indent
import numpy as np
from random import shuffle
from past.builtins import xrange


def svm_loss_naive(W, X, y, reg):
    """
    Structured SVM loss function, naive implementation (with loops).

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
    dW = np.zeros(W.shape)  # initialize the gradient as zero

    # D = W.shape[0]
    # C = W.shape[1]
    # N = X.shape[0]

    # compute the loss and the gradient
    num_classes = W.shape[1]
    num_train = X.shape[0]
    loss = 0.0
    for i in range(num_train):
        scores = X[i].dot(W)  # dot product, calculate score, 1x10
        # y[i] is the label of X[i], this is s_{y_i}
        correct_class_score = scores[y[i]]
        for j in range(num_classes):  # 0 to 9
            if j == y[i]:
                continue
            margin = scores[j] - correct_class_score + 1  # note delta = 1
            if margin > 0:
                loss += margin
                dW[:, j] += X[i].transpose()
                dW[:, y[i]] -= X[i].transpose()

    # Right now the loss is a sum over all training examples, but we want it
    # to be an average instead so we divide by num_train.
    loss /= num_train
    dW /= num_train

    # Add regularization to the loss.
    loss += reg * np.sum(W * W)
    dW += reg * 2 * W

    #############################################################################
    # TODO:                                                                     #
    # Compute the gradient of the loss function and store it dW.                #
    # Rather that first computing the loss and then computing the derivative,   #
    # it may be simpler to compute the derivative at the same time that the     #
    # loss is being computed. As a result you may need to modify some of the    #
    # code above to compute the gradient.                                       #
    #############################################################################
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return loss, dW


def svm_loss_vectorized(W, X, y, reg):
    """
    Structured SVM loss function, vectorized implementation.

    Inputs and outputs are the same as svm_loss_naive.
    """
    loss = 0.0
    dW = np.zeros(W.shape)  # initialize the gradient as zero

    #############################################################################
    # TODO:                                                                     #
    # Implement a vectorized version of the structured SVM loss, storing the    #
    # result in loss.                                                           #
    #############################################################################
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    num_classes = W.shape[1]
    num_train = X.shape[0]
    S = X.dot(W)  # X[N,D], W[D,C], S[N,C]
    X_index = np.arange(num_train)
    # print(X_index)
    correct_class_scores = S[X_index, y]
    # print(f'correct_class_scores.shape={correct_class_scores.shape}', end='')
    S -= correct_class_scores.reshape(-1, 1)
    # print(f'correct_class_scores(reshaped).shape={correct_class_scores.shape}')
    S += 1
    S[X_index, y] = 0
    # print(S)
    loss += np.sum(S*(S > 0))
    loss /= num_train
    loss += reg * np.sum(W*W)

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    #############################################################################
    # TODO:                                                                     #
    # Implement a vectorized version of the gradient for the structured SVM     #
    # loss, storing the result in dW.                                           #
    #                                                                           #
    # Hint: Instead of computing the gradient from scratch, it may be easier    #
    # to reuse some of the intermediate values that you used to compute the     #
    # loss.                                                                     #
    #############################################################################
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    X_T = X.transpose()
    sum_X_T = np.sum(X_T, axis=1)
    sum_X_T.reshape(-1, 1)
    sum_X_T *= num_classes
    dW += sum_X_T[:, np.newaxis]
    print(f'before:\n{dW}')

    D = W.shape[0]
    N = X.shape[0]
    # to_del_X_T = X_T[np.arange(D), y]
    to_del_X_T = np.zeros(W.shape)
    for i in range(num_train):
        to_del_X_T[:, y[i]] += X_T[:, i]

    # dW[:, y] -= to_del_X_T
    dW -= to_del_X_T

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return loss, dW
