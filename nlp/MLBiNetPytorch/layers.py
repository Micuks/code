import torch
from torch.nn import Parameter
import torch.nn as nn
from torch import Tensor
from typing import List, Tuple
from logging import Logger

logger = Logger(__name__)


class LSTMLayer(nn.Module):
    """
    Custom LSTM Layer
    """

    def __init__(self, cell, *cell_args) -> None:
        super(LSTMLayer, self).__init__()
        self.cell = cell(*cell_args)

    def forward(
        self, input: Tensor, state: Tuple[Tensor, Tensor]
    ) -> Tuple[Tensor, Tuple[Tensor, Tensor]]:
        inputs = input.unbind(0)
        outputs = List[Tensor]
        for i in range(len(inputs)):
            out, state = self.cell(inputs[i], state)
            outputs += [out]

        return torch.stack(outputs), state


class LSTMCell(nn.Module):
    """
    Default LSTM Cell
    """

    def __init__(self, input_size, hidden_size) -> None:
        super(LSTMCell, self).__init__()
        self.input_size = input_size
        self.hidden_size = hidden_size
        self.weight_ih = Parameter(torch.randn(4 * hidden_size, input_size))
        self.weight_hh = Parameter(torch.randn(4 * hidden_size, hidden_size))
        self.bias_ih = Parameter(torch.randn(4 * hidden_size))
        self.bias_hh = Parameter(torch.randn(torch.randn(4 * hidden_size)))

    def forward(
        self, input: Tensor, state: Tuple[Tensor, Tensor]
    ) -> Tuple[Tensor, Tuple[Tensor, Tensor]]:
        hx, cx = state
        gates = (
            torch.mm(input, self.weight_ih.t())
            + self.bias_ih
            + torch.mm(hx, self.weight_hh.t())
            + self.bias_hh
        )
        ingate, forgetgate, cellgate, outgate = gates.chunk(4, 1)

        ingate = torch.sigmoid(ingate)
        forgetgate = torch.sigmoid(forgetgate)
        cellgate = torch.sigmoid(cellgate)
        outgate = torch.sigmoid(outgate)

        cy = (forgetgate * cx) + (ingate * cellgate)
        hy = outgate * torch.tanh(cy)

        return hy, (hy, cy)


class PeepHoleLSTMCELL(nn.Module):
    """
    LSTM Cell with peepholes
    """

    def __init__(self, input_size, hidden_size) -> None:
        super(PeepHoleLSTMCELL, self).__init__()
        self.input_size = input_size
        self.hidden_size = hidden_size
        self.weight_ih = Parameter(torch.randn(4 * hidden_size, input_size))
        self.weight_hh = Parameter(torch.randn(4 * hidden_size, hidden_size))
        self.weight_ch = Parameter(torch.randn(4 * hidden_size, hidden_size))
        self.bias_ih = Parameter(torch.randn(4 * hidden_size, hidden_size))
        self.bias_hh = Parameter(torch.randn(4 * hidden_size))
        self.bias_ch = Parameter(torch.randn(4 * hidden_size))

    def forward(
        self, input: Tensor, state: Tuple[Tensor, Tensor]
    ) -> Tuple[Tensor, Tuple[Tensor, Tensor]]:
        hx, cx = state
        gates = (
            (torch.mm(input, self.weight_ih.t()))
            + self.bias_ih
            + torch.mm(hx, self.weight_hh.t() + self.bias_hh)
            + torch.mm(cx, self.weight_ch.t() + self.bias_ch)
        )
        # TODO: computation of cx above may be wrong during (maybe) wrong shape.

        ingate, forgetgate, cellgate, outgate = gates.chunk(4, 1)

        ingate = torch.sigmoid(ingate)
        forgetgate = torch.sigmoid(forgetgate)
        outgate = torch.sigmoid(outgate)
        cellgate = torch.tanh(cellgate)

        cy = (forgetgate * cx) + (ingate * cellgate)
        hy = outgate * torch.tanh(cy)

        return hy, (hy, cy)


class SentenceEncodingLayer(nn.Module):
    """
    Sentence encoding layer to get representation of each words
    """

    def __init__(self, embedding_input, valid_len, name):
        super().__init__()
        self.embedding_input = embedding_input
        self.valid_len = valid_len
        self.name = name
        lstm_cell = {}
        for direction in ["forward", "backward"]:
            lstm_cell[direction] = None
            # TODO: Implement coupled input forget gate lstm cell:
            # that is, LSTM cell with peephole implemented.
