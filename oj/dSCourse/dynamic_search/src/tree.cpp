#include <cstdio>
#include <cstdlib>
#include "../include/tree.h"

Status InitBiTree(BiTree &T) { /* 操作结果: 构造空二叉树T */
    T = NULL;
    return OK;
}

void DestroyTree(BiTree &T) {
    if(T) {
        if(T->lchild)
            DestroyTree(T->lchild);
        if(T->rchild)
            DestroyTree(T->rchild);
        free(T);
        T = NULL;
    }
}

//传入f = NULL
Status SearchBST(BiTree T, ElemType key, BiTree f, BiTree &p) {
    if(!T) {
        p = f;
        return false;
    }
    else if(key == T->data) {
        p = T;
        return true;
    }
    else if(T->data > key) {
        return SearchBST(T->lchild, key, T, p);
    }
    else {
        return SearchBST(T->rchild, key, T, p);
    }
}

Status InsertBST(BiTree &T, ElemType key) {
    BiTNode *pnode = NULL;
    if(!SearchBST(T, key, NULL, pnode)) {
        BiTNode *pnew = (BiTNode*)malloc(sizeof(BiTNode));
        if(!pnew) {
            printf("failed to allocate memory for new node\n");
            return false;
        }
        pnew->data = key;
        pnew->lchild = NULL;
        pnew->rchild = NULL;
        if(!T)
            T = pnew;
        else if(pnode->data > key) {
            printf("%d->lchild = %d\n", pnode->data, pnew->lchild->data);
            pnode->lchild = pnew;
        }
        else {
            pnew->rchild = pnew;
            printf("%d->rchild = %d\n", pnode->data, pnew->rchild->data);
        }
        return true;
    }
    printf("There exists an %d already!\n", key);
    return false;
}

void visit(BiTNode *T) {
    printf("%d ", T->data);
}

void InOrderVisit(BiTree T, void(*visit)(BiTNode *pn)) {
    BiTNode *pnode = T;
    SqStack s;
    InitStack(s);
    printf("StackLength = %ld\n", s.top - s.base);
    while(pnode || !StackEmpty(s)) {
        if(pnode) {
            push(pnode, s);
            pnode = pnode->lchild;
        }
        else {
            pop(pnode, s);
            visit(pnode);
            pnode = pnode->rchild;
        }
    }
}
