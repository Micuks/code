#include "stack.h"

Status InitBiTree(BiTree &T);

void DestroyTree(BiTree &T);

Status InsertBST(BiTree &T, ElemType e);

Status SearchBST(BiTree T, ElemType key, BiTree f, BiTree &p);

void visit(BiTNode *T);

void InOrderVisit(BiTNode *T, void(*visit)(BiTNode *pn));
