#include "sstable.h"

void Merge(ElemType *SR, ElemType *TR, int i, int m, int n);

void Msort(ElemType *SR, ElemType *TR1, int s, int t);

void MergeSort(SSTable &T);

int Search_Bin(SSTable &T, ElemType e);
