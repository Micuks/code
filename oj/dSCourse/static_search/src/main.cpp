#include <cstdio>
#include "../include/algorithm.h"

int main() {
    SSTable SST;
    InitTable(SST);
    int n = 0;
    scanf("%d", &n);
    SST.length = n;
    for(int i = 1; i <= n; i++)
        scanf("%d", &SST.elem[i]);
    MergeSort(SST);

    PrintTable(SST);

    ElemType key = 0;
    scanf("%d", &key);
    int ind = 0;
    ind = Search_Bin(SST, key);
    if(key != SST.elem[ind]) {
        printf("No such element in SSTable!\nInserting...\n");
        ind = InsertTable(SST, key);
    }

    PrintTable(SST);

    printf("SST.elem[%d] = %d\n", ind, SST.elem[ind]);
    DestroyTable(SST);
    return 0;
}
