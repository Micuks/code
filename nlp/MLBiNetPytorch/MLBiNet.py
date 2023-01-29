import os
import torch
import torch.nn as nn
from layers import *
from torch.utils.data import DataLoader
from logging import Logger
from scipy import truncnorm

# Logger setup
logger = logging.getLogger(
    inspect.currentframe().f_code.co_filename.split("/")[-1]
)
logger.setLevel(logging.DEBUG)

con_handler = logging.StreamHandler()
con_handler.setLevel(logging.DEBUG)

formatter = logging.Formatter(
    "%(asctime)s [%(levelname)s] %(name)s L%(lineno)d: %(message)s",
    datefmt="%Y-%m-%DT%H:%M:%S",
    style="%",
)

device = "cuda" if torch.cuda.is_available() else "cpu"
device = "mps" if torch.backends.mps.is_available() else "cpu"
logger.info("Using {} device".format(device))


class MLBiNet(nn.Module):
    def __init__(
        self,
        encode_h,  # hidden size of sentence encoding
        decode_h,  # hidden size of sentence decoding
        tag_dim,  # hidden size of event tag
        event_info_h,  # hidden size of event info integration model
        word_emb_mat,  # word embedding matrix
        batch_size,  # batch size
        max_doc_len,  # max length of doc
        max_seq_len,  # max length of sqeuence
        id_0,  # location of other event/negative event
        num_tag_layers,  # number of tagging layers
        weight_decay,  # weight decay of each tagging layer
        reverse_seq,  # reverse the sequence or not when aggregating information
        class_size,  # class size
        tagging_mechanism="bidirectional_decoder",  # forward_decoder, backward_decoder, bidirectional_decoder
        ner_size_1=None,  # size of level-1 ner embedding
        ner_dim_1=None,  # size of level-2 ner vocab
        ner_size_2=None,  # dimension of level-2 ner embedding
        ner_dim_2=None,  # concat word embedding or not
        self_att_not=1,  # 0: single sentence information, 1: information of two neighbor sentences
        context_info=1,  # non-linear transformation for the event vector
        event_vector_trans=1,
    ) -> None:
        super(MLBiNet, self).__init__()
        self.encode_h = encode_h
        self.decode_h = decode_h
        self.tag_dim = tag_dim
        self.event_info_h = event_info_h
        self.word_emb_mat = word_emb_mat
        self.batch_size = batch_size
        self.max_doc_len = max_doc_len
        self.max_seq_len = max_seq_len
        self.id_0 = id_0
        self.num_tag_layers = num_tag_layers
        self.weight_decay = weight_decay
        self.reverse_seq = reverse_seq
        self.class_size = class_size
        self.tagging_mechanism = tagging_mechanism

        self.ner_size_1 = ner_size_1
        self.ner_dim_1 = ner_dim_1
        self.ner_size_2 = ner_size_2
        self.ner_dim_2 = ner_dim_2
        self.self_att_not = self.self_att_not

        self.context_info = context_info
        self.event_vector_trans = event_vector_trans

        # global initializer
        # xavier_initializer in tensorflow is uniform by default
        self.initializer = torch.nn.init.xavier_uniform_

        # initialize the word embedding matrix
        self.word_emb_mat = self.word_emb_mat.type(torch.float32)
        self.word_embedding_init()

        self.input_docs = torch.zeros(
            self.batch_size,
            self.max_doc_len,
            self.max_seq_len,
            dtype=torch.int32,
        )
        self.ner_docs_1 = torch.zeros(
            self.batch_size,
            self.max_doc_len,
            self.max_seq_len,
            dtype=torch.int32,
        )
        self.ner_docs_2 = torch.zeros(
            self.batch_size,
            self.max_doc_len,
            self.max_seq_len,
            dtype=torch.int32,
        )
        self.input_label_docs = torch.zeros(
            self.batch_size,
            self.max_doc_len,
            self.max_seq_len,
            dtype=torch.int32,
        )
        self.valid_batch = torch.tensor(0, dtype=torch.int32)
        self.valid_sent_len = torch.zeros(self.batch_size, dtype=torch.int32)
        self.valid_words_len = torch.zeros(
            self.batch_size, self.max_doc_len, dtype=torch.int32
        )
        self.dropout_rate = torch.tensor(0, dtype=torch.float32)
        self.positive_weights = torch.tensor(0, dtype=torch.float32)

        # embedding layer
        self.word_embedding_lookup = self.embedding_layer()

        def truncated_normal_(tensor, mean=0, std=1):
            """
            One simple aproximated implementation for truncated_normal to 2*std
            like tensorflow.truncated_normal"""
            a, b = -2 * std, 2 * std
            size = tensor.size
            tmp = tensor.new_empty(size + (4,)).normal_()
            valid = (tmp < b) & (tmp > a)
            ind = valid.max(-1, keepdim=True)[1]
            tensor.data.copy_(tmp.gather(-1, ind).squeeze(-1))
            tensor.data.mul_(std).add_(mean)

        # [unk] event and semantic information aggregation embedding
        self.unk_event_semantic = truncated_normal_(
            tensor=torch.tensor.new_empty((1, self.event_info_h), std=0.1)
        )
        # self.unk_event_semantic = torch.zeros((1, self.event_info_h))

        # sentence encoding layer
        emb_size_curr = list(self.word_embedding_lookup.size())[-1]
        lstm_dropout = torch.nn.Dropout(p=self.dropout_rate)
        self.lstm_inputs = lstm_dropout(self.word_embedding_lookup)

        logger.info(
            "embedding dimension before encoding layer:\t", emb_size_curr
        )

        words_enc, _ = self.sentence_encoding_layer(
            torch.reshape(
                self.lstm_inputs,
                [
                    self.batch_size * self.max_doc_len,
                    self.max_seq_len,
                    emb_size_curr,
                ],
            ),
            self.encode_h,
            torch.reshape(self.valid_words_len, shape=[-1]),
        )

        logger.info(
            f"embedding dimension after encoding layer: {list(words_enc.shape())[-1]}"
        )

        # self-attention
        words_enc = torch.reshape(
            words_enc, (self.batch_size, self.max_doc_len, self.max_seq_len, -1)
        )
        # TODO: Implement self attention layer
        if self.self_att_not:
            words_enc = self.sent_self_att(words_enc, self.valid_words_len)

        logger.info(
            f"embedding dimension after self-attention: {list(words_enc.shape())[-1]}"
        )

    def word_embedding_init(self):
        """
        Initialize the word embedding matrix.

        By default the word embedding matrix is given as parameter.
        """
        if self.word_emb_mat is None:
            logger.error("The embedding matrix must be initialized!")
        else:
            # By default the word embedding matrix is given as parameter.
            pass

    def get_param(
        self, name: str, shape, dtype=None, initializer=None
    ) -> Parameter:
        """
        Get tensor by name.
        If tensor does not exist, initialize a new one with initializer.

        Args:
            name (_type_): tensor name
            shape (_type_): tensor shape
            dtype (_type_, optional): tensor dtype. Defaults to torch.float32.
            initializer (_type_, optional): tensor initializer. Defaults to self.initializer.
        """

        param: Parameter
        try:
            param = self.get_parameter(name)
        except:
            # Tensor does not exist, initialize a new one.
            param = Parameter(initializer(torch.empty(shape, dtype=dtype)))
            self.register_parameter(name=name, param=param)
        return param

    def embedding_layer(self):
        """
        Embedding layer with respect to the word embedding matrix
        """
        embedding_tmp = torch.index_select(
            self.word_emb_mat, 0, self.input_docs
        )

        # looking up the level-1 ner embedding
        if self.ner_size_1 is not None:
            ner_mat_1 = self.get_param(
                name="ner_mat_1",
                shape=(self.ner_size_1, self.ner_dim_1),
                dtype=torch.float32,
                initializer=self.initializer,
            )
            emb_ner1_tmp = torch.index_select(ner_mat_1, 0, self.ner_docs_1)
            embedding_tmp = torch.cat([embedding_tmp, emb_ner1_tmp], dim=-1)

        # lokking up the level-2 ner embedding
        if self.ner_size_2 is not None:
            ner_mat_2 = self.get_param(
                "ner_mat_2",
                (self.ner_size_2, self.ner_dim_2),
                dtype=torch.float32,
                initializer=self.initializer,
            )
            # FIXME: the sequence to be embedded may be self.ner_docs_2 i guess.
            #   Try it.
            emb_ner2_tmp = torch.index_select(ner_mat_2, 0, self.ner_docs_1)
            embedding_tmp = torch.cat([embedding_tmp, emb_ner2_tmp], dim=-1)

    def sentence_encoding_layer(
        embedding_input: Tensor, hidden_size, valid_len, num_layers=1
    ):
        """
        Sentence encoding layer to get representation of each words

        Args:
            embedding_input (_type_): embedding input
            hidden_size (_type_): set to MLBiNet encode_h
            valid_len (_type_): sequence valid length
            num_layers: number of LSTM layers
        """
        _, batch, _ = embedding_input.shape()

        # Initialize hidden states
        #
        # TODO: Used normal initialization here,
        # may need to change to xavier_initializer.
        states = [
            [
                LSTMState(
                    torch.randn(batch, hidden_size),
                    torch.randn(batch, hidden_size),
                )
                for _ in range(2)
            ]
            for _ in range(num_layers)
        ]

        # Bidirectional LSTM layer using peephole LSTM cell.
        # FIXME: input_size of my_lstm may not be valid_len
        peephole_lstm = my_lstm(
            valid_len,
            hidden_size,
            num_layers=num_layers,
            cell=PeepHoleLSTMCell,
            bias=True,
            bidirectional=True,
        )

        out, out_state = peephole_lstm(embedding_input, states)
        peephole_state = double_flatten_states(out_state)

        return out, peephole_state

    def sentence_self_attention(self, words_enc: Tensor, valid_words_len):
        """
        sentence-level self-attention

        Args:
            words_enc (Tensor): batch_size * max_doc_size * max_seq_len * dim
            valid_words_len (_type_): batch_size * max_doc_size
        """
        enc_dim_tmp = list(words_enc.shape())
        words_enc_new0 = torch.reshape(
            words_enc,
            [self.batch_size * self.max_doc_len, self.max_seq_len, enc_dim_tmp],
        )
        valid_words_len_new = torch.reshape(valid_words_len, shape=[-1])

        def self_attention(weight_name="att_W"):
            """
            Sentence level self attention with different window size
            """
            # BUG: replace with get_tensor

            W = self.get_param(
                weight_name,
                shape=(enc_dim_tmp, enc_dim_tmp),
                dtype=torch.float32,
            )
            # x'Wx
            words_enc_new = torch.reshape(
                words_enc,
                (
                    self.batch_size * self.max_doc_len * self.max_seq_len,
                    enc_dim_tmp,
                ),
            )
            words_enc_new = torch.mm(words_enc_new, W)
