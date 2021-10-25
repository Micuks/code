#ifndef LINKLIST_H
#define LINKLIST_H

#include "common.h"

typedef struct {
    float coef;
    int expn;
} ElemType;

typedef struct node {
    ElemType data;
    struct node* prior;
    struct node* next;
} LNode, *LinkList;

typedef LinkList Polynomial;

//在链表中添加一个结点
Status AddElem_L(LinkList &L, ElemType e);

Status AddElemNext_L(LNode *pnode, ElemType e);

Status AddElemPrior_L(LNode *pnode, ElemType e);

//初始化带头结点链表
Status InitList_L(LinkList &L);

//删除链表
void DestroyList_L(LinkList &L);

//Status ClearList_L(LinkList &L);

//Status ListEmpty_L(LinkList L);

//返回链表中结点个数
int ListLength_L(LinkList L);

//Status GetElem_L(LinkList L, int i, ElemType &e);

//int LocateElem_L(LinkList L, ElemType e);

//Status PriorElem_L(LinkList L, ElemType cur_e, ElemType &pre_e);

//Status NextElem_L(LinkList L, ElemType cur_e, ElemType &next_e);

//在第i个结点前插入结点
Status ListInsertPrior_L(LinkList &L, int i, ElemType e);

//在第i个结点后面插入节点
Status ListInsertNext_L(LinkList &L, int i, ElemType e);

//在链表中删除从头开始第i个结点
Status ListDeleteFront_L(LinkList &L, int i, ElemType &e);

//在链表中删除倒数第i个结点
Status ListDeleteRear_L(LinkList &L, int i, ElemType &e);

//删除链表第i个元素的前驱
Status ListDeletePrior_L(LinkList &L, int i, ElemType &e);

//删除链表第i个元素的后继
Status ListDeleteNext_L(LinkList &L, int i, ElemType &e);

//Status ListTraverse_L(LinkList L, void(Visit)(ElemType));

//Status CreateList_HL(LinkList &L, int n);

//Status CreateList_TL(LinkList &L, int n);

//Status Reverse(LinkList C);

//检测链表中是否有环
Status RingExists(LinkList L);

#endif
