#include <cstdio>
#include "../include/tree.h"

int main() {
    BiTree T;
    InitBiTree(T);
    int n;
    ElemType tmp;
    ElemType array[1000] = {0};

    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &tmp);
        array[i] = tmp;
        InsertBST(T, tmp);
    }
    for(int i = 0; i < n; i++) {
        printf("%d\t", i);
    }
    putchar('\n');
    for(int i = 0; i < n; i++) {
        printf("%d\t", array[i]);
    }
    putchar('\n');
    printf("initialized  tree\n");
    InOrderVisit(T, visit);
    putchar('\n');
    DestroyTree(T);

    return 0;
}
