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
        //InsertBST(T, tmp);
    }
    printf("编号\t");
    for(int i = 0; i < n; i++) {
        printf("%d\t", i);
    }
    putchar('\n');
    printf("数据\t");
    for(int i = 0; i < n; i++) {
        printf("%d\t", array[i]);
    }
    putchar('\n');
    for(int i = 0; i < n; i++) {
        InsertBST(T, array[i]);
    }
    printf("中序遍历BST树结果\n");
    InOrderVisit(T, visit);
    putchar('\n');

    int key = 0;
    scanf("%d", &key);
    printf("key = %d\n", key);
    printf("关键字不小于key的元素由大到小输出为\n");
    T4TraverseBST(T, key);

    DestroyTree(T);

    return 0;
}
