#ifndef LINKLIST_H
#define LINKLIST_H

#include "common.h"

typedef int ElemType;
typedef struct node {
    ElemType value;
    struct node* prior;
    struct node* next;
} LNode, *LinkList;

Status InitList_L(LinkList &L);

void DestroyList_L(LinkList &L);

Status ClearList_L(LinkList &L);

Status ListEmpty_L(LinkList L);

int ListLength_L(LinkList L);

Status GetElem_L(LinkList L, int i, ElemType &e);

int LocateElem_L(LinkList L, ElemType e);

Status PriorElem_L(LinkList L, ElemType cur_e, ElemType &pre_e);

Status NextElem_L(LinkList L, ElemType cur_e, ElemType &next_e);

Status ListInsertPrior_L(LinkList &L, int i, ElemType e);

Status ListInsertRear_L(LinkList &L, int i, ElemType e);

Status ListDelete_L(LinkList &L, int i, ElemType e);

Status ListTraverse_L(LinkList L, void(Visit)(ElemType));

Status CreateList_HL(LinkList &L, int n);

Status CreateList_TL(LinkList &L, int n);

Status Reverse(LinkList C);

#endif
