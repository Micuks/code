#include <cstdio>
#include <cstdlib>
#include "../include/algorithm.h"

bool InitTable(SSTable &T) {
    T.elem = (ElemType*)malloc(LIST_INT_SIZE * sizeof(ElemType));
    if(!T.elem) {
        printf("failed to allocate memory\n");
        return false;
    }
    T.length = 0;
    return true;
}

bool DestroyTable(SSTable &T) {
    free(T.elem);
    T.length = 0;
    return true;
}

int InsertTable(SSTable &T, ElemType e) {
    int idx = Search_Bin(T, e);
    if(T.length >= LIST_INT_SIZE) {
        printf("SEGMENT OVERFLOW\n");
        return -1;
    }
    for(int i = ++T.length; i > idx; i--) {
        *(T.elem+i) = *(T.elem+i-1);
    }
    T.elem[idx+1] = e;
    return idx+1;
}

void PrintTable(SSTable T) {
    for(int i = 1; i <= T.length; i++) {
        printf(&"\t%d"[!(i-1)], i);
    }
    putchar('\n');
    for(int i = 1; i <= T.length; i++) {
        printf(&"\t%d"[!(i-1)], T.elem[i]);
    }
    putchar('\n');
}
