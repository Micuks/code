import torch
def sequence_mask(lengths, maxlen=None, dtype=torch.bool):
    """
    Equivalent to sequence_mask in tensorflow

    Args:
        lengths (_type_): lengths of sequences.
        maxlen (_type_, optional): max sequence length. Defaults to None.
        dtype (_type_, optional): mask type. Defaults to torch.bool.
    """
    if maxlen is None:
        maxlen = lengths.max()
    row_vector = torch.arange(0, maxlen, 1)
    matrix = torch.unsqueeze(lengths, dim=-1)
    mask = row_vector < matrix
    mask.type(dtype)
    
    return mask