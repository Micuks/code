#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef struct {
    unsigned int w;
    unsigned int lch, rch, parent;
} HTNode, *HuffmanTree;

typedef char **HuffmanCode;

void select(HuffmanTree &HT, int n, int &s1, int &s2);

void BuildHT(HuffmanTree &HT, unsigned int *w, int n);

void HuffmanCoding(HuffmanTree HT, int n, HuffmanCode &HC);

void HuffManEncoding(HuffmanCode HC, char *ch);

void HuffmanDecoding(HuffmanCode HC, char *ch);
