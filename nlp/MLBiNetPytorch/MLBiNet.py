import os
import torch.nn.functional as F
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

    def info_aggregation_layer(
        self, predict_tag_vector: Tensor, reverse_seq=False
    ):
        """
        Sentence-level event and semantic information aggregation layer

        Args:
            predict_tag_vector (_type_): given sentence vector
            reverse_seq (bool, optional): reverse sequence or not. Defaults to False.
        """
        dim_curr = list(predict_tag_vector.shape)[-1]

        # mask invalid words
        mask_padding_index = self.sequence_mask(
            self.valid_words_len, maxlen=self.max_seq_len, dtype=torch.float32
        )
        mask_padding_index = torch.tile(
            torch.unsqueeze(mask_padding_index, dim=3), dims=(1, 1, 1, dim_curr)
        )
        predict_tag_vector = predict_tag_vector * mask_padding_index

        # reverse the sequence
        if reverse_seq:
            predict_tag_vector = predict_tag_vector[:, :, ::-1, :]
            var_name = "reversed_sentence_info_aggregation_layer"
        else:
            var_name = "sentence_info_aggregation_layer"

        info_aggregation_lstmcell = torch.lstm_cell()
