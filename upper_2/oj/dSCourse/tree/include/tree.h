#include "stack.h"

datatype Nil = '0';

typedef struct csnode {
    datatype data;
    struct csnode *lchild;
    struct csnode *nextsibling;
} SNode, *Tree;

Status InitBiTree(BiTree &T);

void DestroyTree(BiTree &T);

Status CreateBiTree(BiTree &T);

int PostOrderBiTreeDepth(BiTree T);

int PreOrderBiTreeDepth(BiTree T);

int PreOrderBiTreeCount(BiTree T);

void CountDescNum(BiTree T);

int CountLeaves(Tree T);

Status visitT(datatype e);
