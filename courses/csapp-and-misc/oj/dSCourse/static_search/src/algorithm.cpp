#include "../include/algorithm.h"
#include <cstdio>

void Merge(ElemType *SR, ElemType *TR, int i, int m, int n) {
    int j = m+1, k = i;
    for(;j <= n && i <= m; k++) {
        if(SR[i] <= SR[j]) {
            TR[k] = SR[i++];
        }
        else {
            TR[k] = SR[j++];
        }
    }
    for(; i <= m; i++) {
        TR[k++] = SR[i];
    }
    for(; j <= n; j++) {
        TR[k++] = SR[j];
    }
}

void Msort(ElemType *SR, ElemType *TR1, int s, int t) {
    if(s == t)
        TR1[s] = SR[s];
    else {
        ElemType TR2[LIST_INT_SIZE];
        int m = (s+t) >> 1;
        Msort(SR, TR2, s, m);
        Msort(SR, TR2, m+1, t);
        Merge(TR2, TR1, s, m, t);
    }
}

void MergeSort(SSTable &T) {
    Msort(T.elem, T.elem, 1, T.length);
}

int Search_Bin(SSTable &T, ElemType key) {
    int low = 1; int high = T.length;
    while(low <= high) {
        int mid = (low + high) >> 1;
        if(key >= T.elem[mid] && (mid == T.length || T.elem[mid+1] > key)) {
            return mid;
        }
        else {
            if(key < T.elem[mid]) {
                high = mid-1;
            }
            else {
                low = mid+1;
            }
        }
    }
    return 0;
}
