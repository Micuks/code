#!/usr/bin/env python
# -*- coding: utf-8 -*-
from utils import *
import torch.nn.functional as F
from collections import namedtuple
import inspect
import numpy as np
import torch
from torch.nn import Parameter
import torch.nn as nn
from torch import Tensor
from typing import List, Tuple
import logging

logger = logging.getLogger(
    inspect.currentframe().f_code.co_filename.split("/")[-1]
)
logger.setLevel(logging.DEBUG)

con_handler = logging.StreamHandler()
con_handler.setLevel(logging.DEBUG)

formatter = logging.Formatter(
    "%(asctime)s [%(levelname)s] %(name)s L%(lineno)d: %(message)s",
    datefmt="%Y-%m-%dT%H:%M:%S",
    style="%",
)

con_handler.setFormatter(formatter)
logger.addHandler(con_handler)

LSTMState = namedtuple("LSTMState", ["hx", "cx"])


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
        cellgate = torch.tanh(cellgate)
        outgate = torch.sigmoid(outgate)

        cy = (forgetgate * cx) + (ingate * cellgate)
        hy = outgate * torch.tanh(cy)

        return hy, (hy, cy)


def my_lstm(
    input_size,
    hidden_size,
    num_layers,
    cell=LSTMCell,
    bias=True,
    batch_first=False,
    dropout=False,
    dropout_rate=0.4,
    bidirectional=False,
):
    """
    mimics PyTorch naive LSTM with bidirectional LSTM implemented.

    Args:
        input_size (_type_):
        hidden_size (_type_):
        num_layers (_type_):
        cell (_type_, optional): Cell that LSTM will use. Defaults to LSTMCell.
        bias (bool, optional): use bias or not. Defaults to True.
        batch_first (bool, optional): _description_. Defaults to False.
        dropout (bool, optional): _description_. Defaults to False.
        bidirectional (bool, optional): bidirectional or not. Defaults to False.

    Returns:
        _type_: a stack of LSTM layers
    """

    # The following are not implemented.
    assert bias
    assert not batch_first

    if bidirectional:
        stack_type = StackedLSTM2
        layer_type = BidirLSTMLayer
        dirs = 2
    elif dropout:
        stack_type = StackedLSTMWithDropout
        layer_type = LSTMLayer
        dirs = 1
    else:
        stack_type = StackedLSTM
        layer_type = LSTMLayer
        dirs = 1

    if dropout:
        return stack_type(
            num_layers,
            layer_type,
            first_layer_args=[cell, input_size, hidden_size, dropout_rate],
            other_layer_args=[
                cell,
                hidden_size * dirs,
                hidden_size,
                dropout_rate,
            ],
        )
    else:
        return stack_type(
            num_layers,
            layer_type,
            first_layer_args=[cell, input_size, hidden_size],
            other_layer_args=[cell, hidden_size * dirs, hidden_size],
        )


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

        return torch.stack(reverse(outputs)), state


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
    __constants__ = ["layers"]  # Necessary for iterating throuch self.layers

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


class StackedLSTMWithDropout(nn.Module):
    __constants__ = [
        "layers",
        "num_layers",
    ]  # Necessary for iterating through self.layers

    def __init__(
        self,
        num_layers,
        layer,
        first_layer_args,
        other_layer_args,
    ):
        super(StackedLSTMWithDropout, self).__init__()
        self.layers = init_stacked_lstm(
            num_layers, layer, first_layer_args, other_layer_args
        )
        # Introduce a Dropout layer on the outputs of each LSTM layer except the
        # last layer, with dropout probability = 0.4.
        self.num_layers = num_layers

        self.dropout_rate = first_layer_args[-1]

        if num_layers == 1:
            logger.warning(
                "Dropout LSTM adds dropout layers after all but last recurrent"
                "layer, it expects num_layers greater than 1, but got"
                "num_layers = 1."
            )

        self.dropout_layer = nn.Dropout(self.dropout_rate)

    def forward(
        self, input: Tensor, states: List[Tuple[Tensor, Tensor]]
    ) -> Tuple[Tensor, List[Tuple[Tensor, Tensor]]]:
        # List[LSTMState]: One state per layer
        output_states: List[Tuple[Tensor, Tensor]] = []
        output = input

        for i, rnn_layer in enumerate(self.layers):
            state = states[i]
            output, out_state = rnn_layer(output, state)
            # apply the dropoutlayer except the last layer
            if i < self.num_layers - 1:
                output = self.dropout_layer(output)
            output_states += [out_state]

        return output, output_states


class StackedLSTM2(nn.Module):
    """
    Differs from StackedLSTM: its forward method takes
    List[List[Tuple[Tensor, Tensor]]].

    This can also be done by subclassing StackedLSTM.
    """

    __constants__ = ["layers"]  # Necessary for iterating toruch self.layers

    def __init__(self, num_layers, layer, first_layer_args, other_layer_args):
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


class EmbeddingLayer(nn.Module):
    """
    Word embedding layer

    Args:
        nn (_type_): _description_
    """

    def __init__(
        self,
        word_emb_mat: Tensor,
        ner_size_1=None,
        ner_dim_1=None,
        ner_size_2=None,
        ner_dim_2=None,
        initializer=nn.init.xavier_uniform_,
    ) -> Tensor:
        word_emb = nn.Embedding(word_emb_mat.size()[0], word_emb_mat.size()[1])
        word_emb.weight = nn.Parameter(word_emb_mat)
        self.word_emb = word_emb

        if word_emb_mat is None:
            logger.error("The embedding matrix must be initialized!")

        # looking up the level-1 ner embedding
        # FIXME: In origin tensorflow code, ner_mat_1 is got using get_variable().
        if ner_size_1 is not None:
            ner_mat_1 = nn.Embedding(ner_size_1, ner_dim_1)
            ner_mat_1.weight = nn.Parameter(
                initializer(
                    torch.empty(
                        shape=(ner_size_1, ner_dim_1), dtype=torch.float32
                    )
                )
            )
            self.ner_mat_1 = ner_mat_1

        # looking up the level-2 ner embedding
        if ner_size_2 is not None:
            ner_mat_2 = nn.Embedding(ner_size_2, ner_dim_2)
            ner_mat_2.weight = nn.Parameter(
                initializer(
                    torch.empty(
                        shape=(ner_size_2, ner_dim_2), dtype=torch.float32
                    )
                )
            )
            self.ner_mat_2 = ner_mat_2

    def forward(
        self, input_docs: Tensor, ner_docs_1: Tensor, ner_docs_2: Tensor
    ):
        word_emb = self.word_emb
        embedding_tmp = word_emb(input_docs)
        # embedding_tmp = torch.index_select(word_emb_mat, 0, input_docs)

        # looking up the level-1 ner embedding
        # FIXME: In origin tensorflow code, ner_mat_1 is got using get_variable().
        if self.ner_mat_1 is not None:
            ner_mat_1 = self.ner_mat_1
            emb_ner1_tmp = ner_mat_1(ner_docs_1)
            # emb_ner1_tmp = torch.index_select(ner_mat_1, 0, ner_docs_1)
            embedding_tmp = torch.cat((embedding_tmp, emb_ner1_tmp), dim=-1)

        # looking up the level-2 ner embedding
        if self.ner_mat_2 is not None:
            ner_mat_2 = self.ner_mat_2
            # FIXME: the sequence to be embedded may be self.ner_docs_2 i guess.
            # Try it if there is a bug.
            emb_ner2_tmp = ner_mat_2(ner_docs_2)
            # emb_ner2_tmp = torch.index_select(ner_mat_2,0,ner_docs_1)
            embedding_tmp = torch.cat((embedding_tmp, emb_ner2_tmp), dim=-1)

        return embedding_tmp


class SentenceEncodingLayer(nn.Module):
    """
    Sentence encoding layer to get representation of each words

    Args:
        embedding_input (_type_): embedding input
        hidden_size (_type_): set to MLBiNet encode_h
        valid_len (_type_): sequence valid length
        num_layers: number of LSTM layers
    """

    def __init__(
        self,
        input_size: Tensor,
        hidden_size: Tensor,
        valid_len: Tensor,
        num_layers=1,
    ):
        self.input_size = input_size
        self.hidden_size = hidden_size
        self.num_layers = num_layers

        # Bidirectional LSTM layer using peephole LSTM cell.
        self.peephole_lstm = my_lstm(
            input_size,
            hidden_size,
            num_layers=num_layers,
            cell=PeepHoleLSTMCell,
            bias=True,
            bidirectional=True,
        )

    def init_hidden(self, batch_size):
        """
        Init hidden states.

        Args:
            batch_size (_type_): _description_
        """
        states = [
            [
                LSTMState(
                    torch.randn(batch_size, self.hidden_size),
                    torch.randn(batch_size, self.hidden_size),
                )
                for _ in range(2)
            ]
            for _ in range(self.num_layers)
        ]

        return states

    def forward(self, embedding_input, states):
        peephole_lstm = self.peephole_lstm
        states = self.states
        out, out_state = peephole_lstm(embedding_input, states)
        peephole_state = double_flatten_states(out_state)

        return out, peephole_state


class SentenceSelfAttention(nn.Module):
    def __init__(
        self,
        words_enc: Tensor,
        valid_words_len,
        batch_size,
        max_doc_len,
        max_seq_len,
    ):
        """
        sentence-level self-attention with different window size
        """
        enc_dim_tmp = list(words_enc.size())
        words_enc_new0 = torch.reshape(
            words_enc, (batch_size * max_doc_len, max_seq_len, enc_dim_tmp)
        )
        valid_words_len_new = torch.reshape(valid_words_len, shape=(-1))

        W = nn.Parameter(
            torch.empty(enc_dim_tmp, enc_dim_tmp, dtype=torch.float32)
        )

        self.register_parameter("W", W)
        self.W = W
        self.valid_words_len = valid_words_len
        self.batch_size = batch_size
        self.max_doc_len = max_doc_len
        self.max_seq_len = max_seq_len
        self.enc_dim_tmp = enc_dim_tmp
        self.words_enc_new0 = words_enc_new0
        self.valid_words_len_new = valid_words_len_new

    def forward(self, words_enc: Tensor):
        valid_words_len = self.valid_words_len
        batch_size = self.batch_size
        max_doc_len = self.max_doc_len
        max_seq_len = self.max_seq_len
        enc_dim_tmp = self.enc_dim_tmp
        words_enc_new0 = self.words_enc_new0
        valid_words_len_new = valid_words_len_new
        W = self.W

        # x'Wx
        words_enc_new = torch.reshape(
            words_enc, (batch_size * max_doc_len * max_seq_len, enc_dim_tmp)
        )
        words_enc_new = torch.matmul(words_enc_new, W)
        words_enc_new = torch.reshape(
            words_enc_new, (batch_size * max_doc_len, max_seq_len, enc_dim_tmp)
        )
        # tanh(x'Wx)
        logit_self_att = torch.matmul(
            words_enc_new, torch.transpose(words_enc_new0, 1, 2)
        )
        logit_self_att = torch.tanh(logit_self_att)
        probs = F.softmax(logit_self_att, -1)

        # mask invalid words
        mask_words = sequence_mask(
            valid_words_len_new, maxlen=max_seq_len, dtype=torch.float32
        )  # 160*100
        mask_words = torch.tile(
            torch.unsqueeze(mask_words, dim=1), dim=(1, max_seq_len, 1)
        )  # 160*100*100
        probs = probs * mask_words
        probs = torch.matmul(
            torch.diag(1 / (torch.sum(probs, dim=-1) + 1e-8)), probs
        )  # re-standardize the probability
        # attention output
        att_output = torch.matmul(probs, words_enc_new0)
        att_output = att_output.reshape(
            shape=(
                batch_size,
                max_doc_len,
                max_seq_len,
                enc_dim_tmp,
            )
        )

        return att_output


class InfoAggregationLayer(nn.Module):
    def __init__(
        self,
        valid_words_len,
        batch_size,
        max_seq_len,
        max_doc_len,
        event_info_h,
        dropout_rate,
    ):
        """
        Sentence-level event and semantic information aggregation layer

        Args:
        """
        input_size = max_seq_len * max_doc_len
        hidden_size = event_info_h

        initial_states = [
            LSTMState(
                torch.randn(batch_size, hidden_size),
                torch.randn(batch_size, hidden_size),
            )
        ]

        info_aggregation_lstm = my_lstm(
            input_size,
            hidden_size,
            num_layers=1,
            dropout=True,
            dropout_rate=dropout_rate,
        )

        self.info_aggregation_lstm = info_aggregation_lstm
        self.input_size = input_size
        self.max_seq_len = max_seq_len
        self.batch_size = batch_size
        self.max_doc_len = max_doc_len
        self.valid_words_len = valid_words_len

    def forward(self, predict_tag_vector, reverse_seq=False):
        info_aggregation_lstm = self.info_aggregation_lstm
        max_seq_len = self.max_seq_len
        max_doc_len = self.max_doc_len
        input_size = self.input_size
        batch_size = self.batch_size
        valid_words_len = self.valid_words_len

        dim_curr = list(predict_tag_vector.shape)[-1]
        # mask invalid words
        mask_padding_index = sequence_mask(
            valid_words_len, maxlen=max_seq_len, dtype=torch.float32
        )
        mask_padding_index = torch.tile(
            torch.unsqueeze(mask_padding_index, dim=3), dims=(1, 1, 1, dim_curr)
        )
        predict_tag_vector = predict_tag_vector * mask_padding_index

        # reverse the sequence
        if reverse_seq:
            predict_tag_vector = predict_tag_vector[:, :, ::-1, :]

        # sent_event_semantic_info: LSTMState[1]: cell hidden state
        _, (_, sent_event_sematic_info) = info_aggregation_lstm(
            torch.reshape(
                predict_tag_vector, shape=(input_size, max_seq_len, -1)
            )
        )
        sent_event_sematic_info = torch.reshape(
            sent_event_sematic_info, shape=(batch_size, max_doc_len, -1)
        )

        # LSTMState[1] tensor
        return sent_event_sematic_info


class BidirectionalInfoAggregationLayer(nn.Module):
    def __init__(
        self,
        valid_words_len,
        batch_size,
        max_seq_len,
        max_doc_len,
        event_info_h,
        dropout_rate,
    ):
        """
        Bidirectional sentence-level event and semantic info aggregation layer

        Args:
            nn (_type_): _description_
        """
        input_size = max_seq_len * max_doc_len
        hidden_size = event_info_h

        initial_states = [
            LSTMState(
                torch.randn(batch_size, hidden_size),
                torch.randn(batch_size, hidden_size),
            )
        ]

        bidir_info_aggr_lstm = SentenceEncodingLayer(
            input_size,
            hidden_size,
            torch.reshape(valid_words_len, [-1]),
            valid_len=valid_words_len,
        )

        self.bidir_info_aggr_lstm = bidir_info_aggr_lstm
        self.input_size = input_size
        self.batch_size = batch_size
        self.max_seq_len = max_seq_len
        self.max_doc_len = max_doc_len
        self.valid_words_len = valid_words_len

    def forward(self, predict_tag_vector: Tensor, reverse_seq=False):
        """
        Forward

        Args:
            predict_tag_vector (Tensor): shape(batch_size, max_doc_len,
                max_seq_len, word_embedding)
            reverse_seq (bool, optional): _description_. Defaults to False.
        """
        bidir_info_aggr_lstm = self.bidir_info_aggr_lstm
        valid_words_len = self.valid_words_len
        max_seq_len = self.max_seq_len
        max_doc_len = self.max_doc_len
        batch_size = self.batch_size
        input_size = self.input_size

        dim_curr = list(predict_tag_vector.shape)[-1]
        # mask invalid words
        mask_padding_index = sequence_mask(
            valid_words_len, maxlen=max_seq_len, dtype=torch.float32
        )
        mask_padding_index = torch.tile(
            torch.unsqueeze(mask_padding_index, dim=3), dims=(1, 1, 1, dim_curr)
        )
        predict_tag_vector = predict_tag_vector * mask_padding_index

        # reverse the sequence
        if reverse_seq:
            predict_tag_vector = predict_tag_vector[:, :, ::-1, :]

        # sentence_event_semantic_info: LSTMState[1]: cell hidden state
        _, (_, sent_event_semantic_info) = bidir_info_aggr_lstm(
            torch.reshape(
                predict_tag_vector, shape=(input_size, max_seq_len, -1)
            ),
        )

        sent_event_semantic_info = torch.reshape(
            sent_event_semantic_info, shape=(batch_size, max_doc_len, -1)
        )

        return sent_event_semantic_info


class ProjectLayer(nn.Module):
    """

    Args:
        nn (_type_): _description_
    """

    def __init__(self, enc_dim, lstm_dim, initializer=nn.init.xavier_uniform_):
        """
        Project the output of a decoder model to a tag vector

        Args:
            enc_dim (Tensor): list(h_state.shape)[-1]
            lstm_dim (_type_): _description_
            initializer (_type_, optional): _description_. Defaults to nn.init.xavier_uniform_.
        """
        W = Parameter(
            initializer(torch.empty((enc_dim, lstm_dim), dtype=torch.float32))
        )
        b = Parameter(initializer(torch.empty(lstm_dim, dtype=torch.float32)))
        self.W = W
        self.b = b

    def forward(self, h_state):
        W = self.W
        b = self.b
        y_pre = torch.add(torch.matmul(h_state, W), b)
        tag_pre = torch.argmax(F.softmax(y_pre), dim=-1).type(torch.float32)

        return y_pre, tag_pre


class CrossSentenceEDLayer(nn.Module):
    def __init__(
        self,
        words_enc: Tensor,
        event_info_h: Tensor,
        tag_dim,
        enc_dim,
        valid_words_len,
        valid_sent_len,
        num_tag_layers: int,
        event_vector_trans,
        reverse_seq=False,
        initializer=nn.init.xavier_uniform_,
        weight_decay=None,
        batch_size=None,
        max_doc_len=None,
        max_seq_len=None,
        decode_h=None,
        dropout_rate=0.4,
        unk_event_semantic: Tensor = None,
    ):
        """
        Forward-wise cross-sentence event tag event detection,
        modelling the forward-wise event correlation.

        Args:
            words_enc (Tensor): words encoding
            tag_dim (_type_): number of tagging layers
            num_tag_layers (int): number of tagging layers
            weight_decay (_type_): weight decay of tagging vectors of different
                layers.
        """
        input_size = batch_size * max_doc_len
        hidden_size = decode_h

        self.event_info_h = event_info_h
        self.event_vector_trans = event_vector_trans
        self.words_enc = words_enc
        self.tag_dim = tag_dim
        self.enc_dim = enc_dim
        self.num_tag_layers = num_tag_layers
        self.weight_decay = weight_decay
        self.batch_size = batch_size
        self.max_doc_len = max_doc_len
        self.max_seq_len = max_seq_len
        self.decode_h = decode_h
        self.dropout_rate = dropout_rate
        self.unk_event_semantic = unk_event_semantic

        # decoding layer
        # all layers share the same decoder layer
        # for the first decoder layer, set c_{i-1} and c_{i+1} with unk_event_semantic
        self.lstm_outputs = torch.reshape(
            words_enc, shape=(batch_size * max_doc_len, max_seq_len, -1)
        )
        self.decoder_lstm = my_lstm(
            input_size=input_size,
            hidden_size=hidden_size,
            num_layers=1,
            dropout=True,
            dropout_rate=dropout_rate,
        )

        # multi-tagging block
        self.tag_final = torch.zeros(
            (batch_size, max_doc_len, max_seq_len, tag_dim), dtype=torch.float32
        )
        self.tag_final_list = []

        self.init_state = LSTMState(
            torch.zeros(batch_size * max_doc_len, dtype=torch.float32),
            torch.zeros(batch_size * max_doc_len, dtype=torch.float32),
        )
        # event and semantic information of the previous sentence
        # and next sentence
        self.info_event_sem_pre_sentence = unk_event_semantic.tile(
            (batch_size * max_doc_len, 1)
        )
        self.info_event_sem_next_sentence = unk_event_semantic.tile(
            (batch_size * max_doc_len, 1)
        )

        # event and semantice information of the beginning sentence
        self.info_event_sem_init_sentence = unk_event_semantic.tile(
            (batch_size * max_doc_len, 1)
        )
        self.info_event_sem_init_sentence = torch.unsqueeze(
            self.info_event_sem_init_sentence, dim=1
        )
        self.info_event_sem_mat0 = torch.unsqueeze(
            unk_event_semantic, dim=0
        ).tile(dims=(batch_size, max_doc_len, 1))

        self.project = ProjectLayer(enc_dim, tag_dim, initializer)
        self.info_agg_layer = InfoAggregationLayer(
            valid_words_len,
            batch_size,
            max_seq_len,
            max_doc_len,
            event_info_h,
            dropout_rate,
        )

    def forward(self):
        num_tag_layers = self.num_tag_layers
        init_state = self.init_state
        tag_dim = self.tag_dim
        batch_size = self.batch_size
        info_event_sem_pre_sentence = self.info_event_sem_pre_sentence
        info_event_sem_init_sentence = self.info_event_sem_init_sentence
        info_event_sem_next_sentence = self.info_event_sem_next_sentence

        lstm_outputs = self.lstm_outputs
        decoder_lstm = self.decoder_lstm

        for layer_id in range(num_tag_layers):
            # initialize for each layer
            c_state, h_state = init_state
            tag_pre = torch.zeros((batch_size * self.max_doc_len, tag_dim))
            tag_outputs = []
            for time_step in range(self.max_seq_len):
                if self.num_tag_layers > 1:
                    two_info = torch.cat(
                        (
                            info_event_sem_pre_sentence,
                            info_event_sem_next_sentence,
                        ),
                        -1,
                    )
                    input_all = torch.cat(
                        (lstm_outputs[:, time_step, :], two_info, tag_pre),
                        dim=-1,
                    )
                else:
                    input_all = torch.cat(
                        (lstm_outputs[:, time_step, :], two_info, tag_pre),
                        dim=-1,
                    )

                (cell_output, (h_state, c_state)) = decoder_lstm(
                    input_all, (h_state, c_state)
                )

                tag_pre, tag_result = self.project(cell_output)
                if self.event_vector_trans:
                    tag_pre = F.tanh(tag_pre)
                tag_outputs.append(tag_pre)

            tag_outputs = torch.reshape(
                torch.transpose(tag_outputs, 0, 1),
                (self.batch_size, self.max_doc_len, self.max_seq_len, tag_dim),
            )
            if self.num_tag_layers > 1:
                # info aggregation of current sentence, (batch_size,
                # max_doc_len, event_info_h)
                info_event_sem_current_sentence = self.info_agg_layer(
                    tag_outputs, reverse_seq=False
                )

                # corresponds to the information of previous sentence
                info_event_sem_pre_sentence = torch.cat(
                    (
                        info_event_sem_init_sentence,
                        info_event_sem_current_sentence[:, :-1, :],
                    ),
                    dim=1,
                )
                info_event_sem_pre_sentence = torch.reshape(
                    info_event_sem_pre_sentence,
                    shape=(self.batch_size * self.max_doc_len, -1),
                )

                # find valid sentence firstly, and replace with embedding of unk
                info_event_sem_current_sentence_backward = self.info_agg_layer(
                    tag_outputs, reverse_seq=self.reverse_seq
                )
                valid_sentence_index = sequence_mask(
                    self.valid_sent_len,
                    maxlen=self.max_doc_len,
                    dtype=torch.float32,
                )

                valid_sentence_index = torch.tile(
                    torch.unsqueeze(valid_sentence_index, dim=2),
                    dims=(1, 1, self.event_info_h),
                )
                info_event_sem_current_sentence_backward = (
                    info_event_sem_current_sentence_backward
                    * valid_sentence_index
                    + self.info_event_sem_mat0 * (1 - valid_sentence_index)
                )

                # corresponding to the information of previous sentence
                info_event_sem_next_sentence = torch.cat(
                    (
                        info_event_sem_current_sentence_backward[:, 1:, :],
                        info_event_sem_init_sentence,
                    ),
                    dim=1,
                )
                info_event_sem_next_sentence = torch.reshape(
                    info_event_sem_next_sentence,
                    shape=(self.batch_size * self.max_doc_len, -1),
                )
            self.tag_final += self.weight_decay**layer_id * tag_outputs
            self.tag_final_list.append(tag_outputs)
        return self.tag_final, self.tag_final_list


class BackwardCrossSentenceEDLayer(nn.Module):
    def __init__(
        self,
        words_enc: Tensor,
        event_info_h: Tensor,
        tag_dim,
        enc_dim,
        valid_words_len,
        valid_sent_len,
        num_tag_layers: int,
        event_vector_trans,
        initializer=nn.init.xavier_uniform_,
        reverse_seq=False,
        weight_decay=None,
        batch_size=None,
        max_doc_len=None,
        max_seq_len=None,
        decode_h=None,
        dropout_rate=0.4,
        unk_event_semantic: Tensor = None,
    ):
        """

        Backward-wise cross-sentence event ta event detection, modeling the
        backward-wise event correlation.

        Args:
            words_enc (Tensor): words encoding
            event_info_h (Tensor): _description_
            tag_dim (_type_): numeber of tagging layers
            enc_dim (_type_): _description_
            valid_words_len (_type_): _description_
            valid_sent_len (_type_): _description_
            num_tag_layers (int): number of tagging layers
            event_vector_trans (_type_): _description_
            initializer (_type_, optional): _description_. Defaults to nn.init.xavier_uniform_.
            weight_decay (_type_, optional): weight decay of taggin vectors of
                different layers. Defaults to None.
            batch_size (_type_, optional): _description_. Defaults to None.
            max_doc_len (_type_, optional): _description_. Defaults to None.
            max_seq_len (_type_, optional): _description_. Defaults to None.
            decode_h (_type_, optional): _description_. Defaults to None.
            dropout_rate (float, optional): _description_. Defaults to 0.4.
            unk_event_semantic (Tensor, optional): _description_. Defaults to None.
        """
        input_size = batch_size * max_doc_len
        hidden_size = decode_h

        self.event_info_h = event_info_h
        self.event_vector_trans = event_vector_trans
        self.words_enc = words_enc
        self.tag_dim = tag_dim
        self.enc_dim = enc_dim
        self.num_tag_layers = num_tag_layers
        self.weight_decay = weight_decay
        self.batch_size = batch_size
        self.max_doc_len = max_doc_len
        self.max_seq_len = max_seq_len
        self.decode_h = decode_h
        self.dropout_rate = dropout_rate
        self.unk_event_semantic = unk_event_semantic

        self.lstm_outputs = torch.reshape(
            words_enc,
            shape=(self.batch_size * self.max_doc_len, self.max_seq_len, -1),
        )
        self.lstm_outputs = self.lstm_outputs[:, ::-1, :]
        self.decoder_lstm = my_lstm(
            input_size=input_size,
            hidden_size=hidden_size,
            num_layers=1,
            dropout=True,
            dropout_rate=dropout_rate,
        )

        # multi-tagging block
        self.tag_final = torch.zeros(
            shape=(
                self.batch_size,
                self.max_doc_len,
                self.max_seq_len,
                tag_dim,
            ),
            dtype=torch.float32,
        )
        self.tag_final_list = []
        self.init_state = LSTMState(
            torch.zeros(self.batch_size * self.max_doc_len, dtype=torch.float32)
        )

        # event and semantic information of the previous sentence and next sentence
        self.info_event_semantic_pre_sentence = torch.tile(
            self.unk_event_semantic,
            dims=(self.batch_size * self.max_doc_len, 1),
        )
        self.info_event_semantic_next_sentence = torch.tile(
            self.unk_event_semantic,
            dims=(self.batch_size * self.max_doc_len, 1),
        )

        # event and semantic information of the final sentence
        self.info_event_semantic_init_sentence = torch.tile(
            self.unk_event_semantic, dims=(self.batch_size, 1)
        )
        self.info_event_semantic_init_sentence = torch.unsqueeze(
            self.info_event_semantic_init_sentence, dim=1
        )
        self.info_event_sem_mat0 = torch.tile(torch.expand_dims(self))
        self.project = ProjectLayer(enc_dim, tag_dim, initializer)
        self.info_agg_layer = InfoAggregationLayer(
            valid_words_len,
            batch_size,
            max_seq_len,
            max_doc_len,
            event_info_h,
            dropout_rate,
        )
        self.reverse_seq = reverse_seq
        self.valid_sent_len = valid_sent_len

    def forward(self):
        num_tag_layers = self.num_tag_layers
        init_state = self.init_state
        info_event_semantic_pre_sentence = self.info_event_semantic_pre_sentence
        info_event_semantic_init_sentence = (
            self.info_event_semantic_init_sentence
        )
        info_event_semantic_next_sentence = (
            self.info_event_semantic_next_sentence
        )
        lstm_outputs = self.lstm_outputs
        decoder_lstm = self.decoder_lstm
        tag_dim = self.tag_dim
        info_event_sem_mat0 = self.info_event_sem_mat0
        tag_final = self.tag_final
        weight_decay = self.weight_decay
        tag_final_list = self.tag_final_list

        for layer_id in range(num_tag_layers):
            # initialize for each layer
            h_state, c_state = init_state
            tag_next = torch.zeros(
                (self.batch_size * self.max_doc_len, tag_dim)
            )
            tag_outputs = []
            for time_step in range(self.max_seq_len):
                if self.num_tag_layers > 1:
                    two_info = torch.cat(
                        (
                            info_event_semantic_pre_sentence,
                            info_event_semantic_next_sentence,
                        ),
                        dim=-1,
                    )
                    input_all = torch.cat(
                        (lstm_outputs[:, time_step, :], two_info, tag_next),
                        dim=-1,
                    )
                else:
                    input_all = torch.cat(
                        (lstm_outputs[:, time_step, :], tag_next), dim=-1
                    )
                (cell_output, (h_state, c_state)) = decoder_lstm(
                    input_all, (h_state, c_state)
                )
                tag_next, tag_result = self.project(cell_output)
                if self.event_vector_trans:
                    tag_next = torch.tanh(tag_next)
                tag_outputs.append(tag_next)
            tag_outputs = torch.reshape(
                torch.transpose(tag_outputs, 0, 1),
                shape=(
                    self.batch_size,
                    self.max_doc_len,
                    self.max_seq_len,
                    tag_dim,
                ),
            )

            # recover the tag_outputs in order
            tag_outputs = tag_outputs[:, :, ::-1, :]

            if self.num_tag_layers > 1:
                # info aggregation of current sentence,
                # [batch_size, max_doc_len, event_info_h]
                info_event_semantic_current_sentence = self.info_agg_layer(
                    tag_outputs, reverse_seq=self.reverse_seq
                )

                # find valid sentence firstly, and replace with embedidng of unk
                valid_sentence_index = sequence_mask(
                    self.valid_sent_len,
                    maxlen=self.max_doc_len,
                    dtype=torch.float32,
                )
                valid_sentence_index = torch.tile(
                    torch.unsqueeze(valid_sentence_index, dim=2),
                    dims=(1, 1, self.event_info_h),
                )
                info_event_semantic_current_sentence = (
                    info_event_semantic_current_sentence * valid_sentence_index
                    + info_event_sem_mat0 * (1 - valid_sentence_index)
                )

                # corresponds to the information of previous sentence
                info_event_semantic_next_sentence = torch.cat(
                    (
                        info_event_semantic_current_sentence[:, 1:, :],
                        info_event_semantic_init_sentence,
                    ),
                    dim=1,
                )
                info_event_semantic_next_sentence = torch.reshape(
                    info_event_semantic_next_sentence,
                    shape=(self.batch_size * self.max_doc_len, -1),
                )

                # information of previous sentence,
                # [batch_size, max_doc_len, event_info_h]
                info_event_semantic_current_sentence = self.info_agg_layer(
                    tag_outputs, reverse_seq=False
                )
                info_event_semantic_pre_sentence = torch.cat(
                    (
                        info_event_semantic_init_sentence,
                        info_event_semantic_current_sentence[:, :-1, :],
                    ),
                    dim=1,
                )
                info_event_semantic_pre_sentence = torch.reshape(
                    info_event_semantic_pre_sentence, 
                    shape=(self.batch_size*self.max_doc_len, -1)
                )
            tag_final += weight_decay**layer_id*tag_outputs
            tag_final_list.append(tag_outputs)
        return tag_final, tag_final_list


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

    logger.info("LSTM layer test:")
    logger.info(
        "(custom_out - lstn_out).abs().max(): {}".format(
            (custom_out - lstm_out).abs().max()
        )
    )
    assert (custom_out - lstm_out).abs().max() < 1e-5
    logger.info(
        "(custom_out_state[0] - lstm_out_state[0]).abs().max(): {}".format(
            (custom_out_state[0] - lstm_out_state[0]).abs().max()
        )
    )
    assert (custom_out_state[0] - lstm_out_state[0]).abs().max() < 1e-5
    logger.info(
        "(custom_out_state[1] - lstm_out_state[1]).abs().max(): {}".format(
            (custom_out_state[1] - lstm_out_state[1]).abs().max()
        )
    )
    assert (custom_out_state[1] - lstm_out_state[1]).abs().max() < 1e-5


def flatten_states(states):
    states = list(zip(*states))
    assert len(states) == 2
    return [torch.stack(state) for state in states]


def double_flatten_states(states):
    """
    Flatten hidden state of bidirectional LSTM(List[List[Tuple[Tensor, Tensor]]])
    into PyTorch hidden state format.

    Args:
        states (List[List[Tuple[Tensor, Tensor]]]): states to be flattened

    Returns:
        _type_: flattened states
    """
    logger = logging.getLogger(
        "{}.{}".format(
            inspect.currentframe().f_code.co_filename.split("/")[-1],
            inspect.currentframe().f_code.co_name,
        )
    )

    states = flatten_states([flatten_states(inner) for inner in states])
    logger.debug(f"len(states)={len(states)}, hidden.shape={states[0].shape}")
    assert len(states) == 2
    return [hidden.view([-1] + list(hidden.shape[2:])) for hidden in states]


def test_stacked_lstm(seq_len, batch, input_size, hidden_size, num_layers):
    inp = torch.randn(seq_len, batch, input_size)
    states = [
        LSTMState(
            torch.randn(batch, hidden_size), torch.randn(batch, hidden_size)
        )
        for _ in range(num_layers)
    ]
    custom_lstm = my_lstm(input_size, hidden_size, num_layers)
    custom_out, custom_out_state = custom_lstm(inp, states)
    custom_state = flatten_states(custom_out_state)

    # Control: PyTorch native LSTM
    lstm = nn.LSTM(input_size, hidden_size, num_layers)
    lstm_state = flatten_states(states)
    for layer in range(num_layers):
        custom_params = list(custom_lstm.parameters())[
            4 * layer : 4 * (layer + 1)
        ]
        for lstm_param, custom_param in zip(
            lstm.all_weights[layer], custom_params
        ):
            assert lstm_param.shape == custom_param.shape
            with torch.no_grad():
                lstm_param.copy_(custom_param)
    lstm_out, lstm_out_state = lstm(inp, lstm_state)

    logger.info("Stacked LSTM test:")
    logger.info(
        f"(custom_out - lstm_out).abs().max(): {(custom_out - lstm_out).abs().max()}"
    )
    assert (custom_out - lstm_out).abs().max() < 1e-5
    logger.info(
        f"(custom_state[0] - lstm_out_state[0]).abs().max(): {(custom_state[0] - lstm_out_state[0]).abs().max()}"
    )
    assert (custom_state[0] - lstm_out_state[0]).abs().max() < 1e-5
    logger.info(
        f"(custom_state[1] - lstm_out_state[1]).abs().max(): {(custom_state[1] - lstm_out_state[1]).abs().max()}"
    )
    assert (custom_state[1] - lstm_out_state[1]).abs().max() < 1e-5


def test_stacked_bidir_lstm(
    seq_len, batch, input_size, hidden_size, num_layers
):
    inp = torch.randn(seq_len, batch, input_size)
    states = [
        [
            LSTMState(
                torch.randn(batch, hidden_size), torch.randn(batch, hidden_size)
            )
            for _ in range(2)
        ]
        for _ in range(num_layers)
    ]
    custom_lstm = my_lstm(
        input_size, hidden_size, num_layers, bidirectional=True
    )
    custom_out, custom_out_state = custom_lstm(inp, states)
    custom_state = double_flatten_states(custom_out_state)

    # Control: PyTorch native LSTM
    lstm = nn.LSTM(input_size, hidden_size, num_layers, bidirectional=True)
    lstm_state = double_flatten_states(states)
    for layer in range(num_layers):
        for direction in range(2):
            index = 2 * layer + direction
            custom_params = list(custom_lstm.parameters())[
                4 * index : 4 * index + 4
            ]
            for lstm_param, custom_param in zip(
                lstm.all_weights[index], custom_params
            ):
                assert lstm_param.shape == custom_param.shape
                with torch.no_grad():
                    lstm_param.copy_(custom_param)
    lstm_out, lstm_out_state = lstm(inp, lstm_state)

    logger.info("Stacked Bidirectional LSTM test:")
    logger.info(
        f"(custom_out - lstm_out).abs().max(): {(custom_out - lstm_out).abs().max()}"
    )
    assert (custom_out - lstm_out).abs().max() < 1e-5
    logger.info(
        f"(custom_state[0] - lstm_out_state[0]).abs().max(): {(custom_state[0] - lstm_out_state[0]).abs().max()}"
    )
    assert (custom_state[0] - lstm_out_state[0]).abs().max() < 1e-5
    logger.info(
        f"(custom_state[1] - lstm_out_state[1]).abs().max(): {(custom_state[1] - lstm_out_state[1]).abs().max()}"
    )
    assert (custom_state[1] - lstm_out_state[1]).abs().max() < 1e-5


test_lstm_layer(5, 2, 3, 7)
test_stacked_lstm(5, 2, 3, 7, 4)
test_stacked_bidir_lstm(5, 2, 3, 7, 4)
