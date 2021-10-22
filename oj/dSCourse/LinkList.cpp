#include <stdlib.h>
#include <stdio.h>
#include "LinkList.hpp"

Status AllocateNode(LNode* s) {
    s = (LNode*)malloc(sizeof(LNode));
    if(s == NULL)
        exit(OVERFLOW);
    else return TRUE;
}

//在p结点后插入s结点
Status ListInsertRear_L(LinkList &L, int i, ElemType e) {
    //长为n的链表的下标范围为0到n-1
    LNode* pnode = L;
    if(L == NULL)
        exit(OVERFLOW);
    int ind = 0;
    while(ind != i-1 && pnode->next != NULL) {
        pnode = pnode->next;
    }
    LNode* pn2 = pnode->next;
    if(ind != i-1)
        exit(OVERFLOW);
    LNode* ps;
    AllocateNode(ps);
    if(ps == NULL)
        exit(OVERFLOW);
    pnode->next = ps;
    ps->prior = pnode;
    ps->next = pn2;
    if(pn2 != NULL)
        pn2->prior = ps;
    return TRUE;
}

//在p结点前插入s结点
Status ListInsertPrior_L(LinkList &L, int i, ElemType e) {
    LNode* pnode = L;
    if(L == NULL)
        exit(OVERFLOW);
    int ind = 0;
    while(ind != i-1) {
        pnode = pnode->next;
    }
    if(ind != i-1)
        exit(OVERFLOW);
    LNode* pn2 = pnode->prior;
    LNode* ps;
    AllocateNode(ps);
    if(ps == NULL)
        exit(OVERFLOW);
    pn2->next = ps;
    ps->prior = pn2;
    ps->next = pnode;
    pnode->prior = ps;
    return TRUE;
}

//删除p结点的直接后继节点
Status ListDeleteRear_L(LinkList &L, int i, ElemType &e) {
    LNode *pnode = L;
    if(L == NULL)
        exit(OVERFLOW);
    int ind = 0;
    while(ind != i-1 && pnode->next != NULL)
        pnode = pnode->next;
    if(ind != i-1 || pnode->next == NULL)
        exit(OVERFLOW);
    LNode *ptmp = pnode->next;
    pnode->next = pnode->next->next;
    if(pnode->next != NULL) {
        pnode->next->prior = pnode;
        e = ptmp->value;
        free(ptmp);
    }
    return TRUE;
}

Status ListDeletePrior_L(LinkList &L, int i, ElemType &e) {
    LNode *pnode = L;
    if(L == NULL)
        exit(OVERFLOW);
    int ind = 0;
    while(ind != i-1 && pnode->next != NULL)
        pnode = pnode->next;
    if(ind != i-1)
        exit(OVERFLOW);
    LNode *ptmp = pnode->prior;
    pnode->prior = pnode->prior->prior;
    pnode->prior->next = pnode;
    e = ptmp->value;
    free(ptmp);
    return TRUE;
}

Status ListDelete_L(LinkList &L, int i, ElemType &e) {
    LNode *pnode = L;
    if(L == NULL)
        exit(OVERFLOW);
    int ind = 0;
    while(ind != i-1 && pnode->next != NULL)
        pnode = pnode->next;
    if(ind != i-1)
        exit(OVERFLOW);
    e = pnode->value;
    free(pnode);
    return TRUE;
}
