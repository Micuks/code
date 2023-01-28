from collections import namedtuple
import torch
from torch.nn import Parameter
import torch.nn as nn
from torch import Tensor
from typing import List, Tuple
from logging import Logger

logger = Logger(__name__)

LSTMState = namedtuple("LSTMState", ["hx", "cx"])


def lstm(
    input_size,
    hidden_size,
    num_layers,
    bias=True,
    batch_first=False,
    dropout=False,
    bidirectional=False,
):
    """
    mimics PyTorch naive LSTM with bidirectional LSTM implemented.
    """
    # The following are not implemented.
    assert bias
    assert dropout
    assert not batch_first

    if bidirectional:
        stack_type = StackedLSTM2
        layer_type = BidirLSTMLayer
        dirs = 2
    else:
        stack_type = StackedLSTM
        layer_type = LSTMLayer
        dirs = 1

    return stack_type(
        num_layers,
        layer_type,
        first_layer_args=[LSTMCell, input_size, hidden_size],
        other_layer_args=[LSTMCell, hidden_size * dirs, hidden_size],
    )


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
        self.bias_hh = Parameter(torch.randn(4 * hidden_size))

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


class PeepHoleLSTMCell(nn.Module):
    """
    LSTM Cell with peepholes
    """

    def __init__(self, input_size, hidden_size) -> None:
        super(PeepHoleLSTMCell, self).__init__()
        self.input_size = input_size
        self.hidden_size = hidden_size
        self.weight_ih = Parameter(torch.randn(4 * hidden_size, input_size))
        self.weight_hh = Parameter(torch.randn(4 * hidden_size, hidden_size))
        self.weight_ch = Parameter(torch.randn(4 * hidden_size, hidden_size))
        self.bias_ih = Parameter(torch.randn(4 * hidden_size))
        self.bias_hh = Parameter(torch.randn(4 * hidden_size))
        self.bias_ch = Parameter(torch.randn(4 * hidden_size))

    def reset_parameters(self) -> None:
        """
        The same initialization method as LSTM in nn.Module.
        """
        std = 1.0 / self.hidden_size
        for w in self.parameters():
            w.data.uniform_(-std, std)

    def forward(
        self, input: Tensor, state: Tuple[Tensor, Tensor]
    ) -> Tuple[Tensor, Tuple[Tensor, Tensor]]:
        hx, cx = state
        gates = (
            (torch.mm(input, self.weight_ih.t()))
            + self.bias_ih
            + torch.mm(hx, self.weight_hh.t())
            + self.bias_hh
            + torch.mm(cx, self.weight_ch.t())
            + self.bias_ch
        )

        ingate, forgetgate, cellgate, outgate = gates.chunk(4, 1)

        ingate = torch.sigmoid(ingate)
        forgetgate = torch.sigmoid(forgetgate)
        outgate = torch.sigmoid(outgate)
        cellgate = torch.tanh(cellgate)

        cy = (forgetgate * cx) + (ingate * cellgate)
        hy = outgate * torch.tanh(cy)

        return hy, (hy, cy)


class GRUCell(nn.Module):
    """
    GRU(Gated Recurrent Unit) Cell

    Combines the forget and input gate into update gate which is newly added in
    this architecture. It also merges the cell state and hidden state. The
    resulting model is simpler than traditional LSTM.
    """

    def __init__(self, input_size, hidden_size, bias=True) -> None:
        super(GRUCell, self).__init__()
        self.input_size = input_size
        self.hidden_size = hidden_size
        self.bias = bias
        self.weight_ih = Parameter(torch.randn(3 * hidden_size, input_size))
        self.weight_rh = Parameter(torch.randn(3 * hidden_size, hidden_size))
        self.bias_ih = Parameter(torch.randn(3 * hidden_size))
        self.bias_rh = Parameter(torch.randn(3 * hidden_size))

    def reset_parameters(self) -> None:
        """
        The same initialization method as LSTM in nn.Module.
        """
        std = 1.0 / self.hidden_size
        for w in self.parameters():
            w.data.uniform_(-std, std)

    def forward(self, input: Tensor, state: Tensor) -> Tensor:
        hx = state
        gates_x = torch.mm(input, self.weight_ih.t()) + (
            self.bias_ih if self.bias else 0
        )
        gates_h = +torch.mm(hx, self.weight_rh.t()) + (
            self.bias_rh if self.bias else 0
        )

        ingate_x, resetgate_x, newgate_x = gates_x.chunk(3, 1)
        ingate_h, resetgate_h, newgate_h = gates_h.chunk(3, 1)

        ingate = torch.sigmoid(ingate_x + ingate_h)
        resetgate = torch.sigmoid(resetgate_x + resetgate_h)
        newgate = torch.tanh(newgate_h * resetgate + newgate_x)

        hy = (1 - ingate) * hx + resetgate * newgate

        return hy


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
        outputs: List[Tensor] = []
        for i in range(len(inputs)):
            out, state = self.cell(inputs[i], state)
            outputs += [out]

        return torch.stack(outputs), state


def reverse(lst: List[Tensor]) -> List[Tensor]:
    """
    Reverse input list
    """
    return lst[::-1]


class ReverseLSTMLayer(nn.Module):
    def __init__(self, cell, *cell_args):
        super(ReverseLSTMLayer, self).__init__()
        self.cell = cell(*cell_args)

    def forward(
        self, input: Tuple, state: Tuple[Tensor, Tensor]
    ) -> Tuple[Tensor, Tuple[Tensor, Tensor]]:
        inputs = reverse(input.unbind(0))
        outputs: List[Tensor] = []
        for i in range(len(inputs)):
            out, state = self.cell(inputs[i], state)
            outputs += [out]

        return torch.stack(reverse(outputs), state)


class BidirLSTMLayer(nn.Module):
    __constants__ = ["direcitons"]

    def __init__(self, cell, *cell_args):
        super(BidirLSTMLayer, self).__init__()
        self.directions = nn.ModuleList(
            [LSTMLayer(cell, *cell_args), ReverseLSTMLayer(cell, *cell_args)]
        )

    def forward(
        self, input: Tensor, states: List[Tuple[Tensor, Tensor]]
    ) -> Tuple[Tensor, List[Tuple[Tensor, Tensor]]]:
        # List[LSTMState]: [forward state, backward state]
        outputs: List[Tensor] = []
        output_states: List[Tuple[Tensor, Tensor]] = []

        for i, direction in enumerate(self.directions):
            state = states[i]
            out, out_state = direction(input, state)
            outputs += [out]
            output_states += [out_state]

        return torch.cat(outputs, -1), output_states


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
            # TODO: Use xavier initializer as default initializer
            lstm_cell[direction] = PeepHoleLSTMCell(
                embedding_input, self.encode_h
            )

        (
            output,
            (encoder_fw_final_state, encoder_bw_final_state),
        ) = BidirLSTMLayer(
            lstm_cell["forward"], lstm_cell["backward"], embedding_input
        )


def init_stacked_lstm(num_layers, layer, first_layer_args, other_layer_args):
    """Initialize layers with given layer args

    Args:
        num_layers: Number of layers
        layer: Layer
        first_layer_args: Args of first layer
        other_layer_args: Args of second layer

    Returns:
        nn.ModuleList: A list of initialized layers
    """
    layers = [layer(*first_layer_args)] + [
        layer(*other_layer_args) for _ in range(num_layers - 1)
    ]
    return nn.ModuleList(layers)


class StackedLSTM(nn.Module):
    __constants__ = ["layers"]  # Necessary for interating throuch self.layers

    def __init__(self, num_layers, layer, first_layer_args, other_layer_args):
        super(StackedLSTM, self).__init__()
        self.layers = init_stacked_lstm(
            num_layers, layer, first_layer_args, other_layer_args
        )

    def forward(
        self, input: Tensor, states: List[Tuple[Tensor, Tensor]]
    ) -> Tuple[Tensor, List[Tuple[Tensor, Tensor]]]:
        # List[LSTMState]: One state per layer
        output_states: List[Tuple[Tensor, Tensor]] = []
        output = input
        for i, rnn_layer in enumerate(self.layers):
            state = states[i]
            output, out_state = rnn_layer(output, state)
            output_states += [out_state]

        return output, output_states


class StackedLSTM2(nn.Module):
    """
    Differs from StackedLSTM: its forward method takes
    List[List[Tuple[Tensor, Tensor]]].

    This can also be done by subclassing StackedLSTM.
    """

    __constants__ = ["layers"]  # Necessary for iterating toruch self.layers

    def __init(self, num_layers, layer, first_layer_args, other_layer_args):
        super(StackedLSTM2, self).__init__()
        self.layers = init_stacked_lstm(
            num_layers, layer, first_layer_args, other_layer_args
        )

    def forward(
        self, input: Tensor, states: List[List[Tuple[Tensor, Tensor]]]
    ) -> Tuple[Tensor, List[List[Tuple[Tensor, Tensor]]]]:
        # List[List[LSTMState]]: the outer list is for layers,
        # inner list is for directions
        output_states: List[List[Tuple[Tensor, Tensor]]] = []
        output = input
        for i, rnn_layer in enumerate(self.layers):
            state = states[i]
            output, out_state = rnn_layer(output, state)
            output_states += [out_state]

        return output, output_states


def test_lstm_layer(seq_len, batch, input_size, hidden_size):
    inp = torch.randn(seq_len, batch, input_size)
    state = LSTMState(
        torch.randn(batch, hidden_size), torch.randn(batch, hidden_size)
    )
    custom_lstm = LSTMLayer(LSTMCell, input_size, hidden_size)
    custom_out, custom_out_state = custom_lstm(inp, state)

    # Control: pytorch native LSTM
    lstm = nn.LSTM(input_size, hidden_size, 1)
    lstm_state = LSTMState(state.hx.unsqueeze(0), state.cx.unsqueeze(0))
    for lstm_param, custom_param in zip(
        lstm.all_weights[0], custom_lstm.parameters()
    ):
        assert lstm_param.shape == custom_param.shape
        with torch.no_grad():
            lstm_param.copy_(custom_param)

    lstm_out, lstm_out_state = lstm(inp, lstm_state)

    assert (custom_out - lstm_out).abs().max() < 1e-5
    assert (custom_out_state[0] - lstm_out_state[0]).abs().max() < 1e-5
    assert (custom_out_state[1] - lstm_out_state[1]).abs().max() < 1e-5
