#include <cstdio>
#include <cstring>
#include <cstdlib>

const int maxn = 1000;

typedef struct {
    int w;
    int lch, rch, parent;
} HTNode, *HuffmanTree;

typedef char **HuffmanCode;

void select(HuffmanTree &HT, int n, int &s1, int &s2);

void BuildHT(HuffmanTree &HT, int *w, int n);

void HuffmanCoding(HuffmanTree HT, int n, HuffmanCode &HC);

void HuffManEncoding(HuffmanCode HC, char *src, char **dest);

void HuffmanDecoding(HuffmanCode HC, char **src, char *dest);
