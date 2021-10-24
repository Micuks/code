#include <stdlib.h>
#include <stdio.h>
#include "../include/LinkList.hpp"

//初始化带头结点链表
Status InitList_L(LinkList &L) {
    L = (LinkList)malloc(sizeof(LNode));
    if(L == NULL)
        return FALSE;
    L->data.expn = -1;
    return TRUE;
}

//在链表中添加一个结点
Status AddElem_L(LinkList &L, ElemType e) {
    LNode* pnew = (LNode*)malloc(sizeof(LNode));
    if(pnew == NULL) {
        printf("Failed to allocate space! --AddElem_L\n");
        return FALSE;
    }
    LNode* pnode = L;
    while(pnode->next != NULL)
        pnode = pnode->next;
    pnew->next = NULL;
    pnew->prior = pnode;
    pnode->next = pnew;
    return TRUE;
}

//在p结点后插入s结点
Status ListInsertNext_L(LinkList &L, int i, ElemType e) {
    //长为n的链表的下标范围为0到n-1
    LNode* pnode = L;
    if(L == NULL)
        return FALSE;
    int ind = 0;
    while(ind != i && pnode->next != NULL) {
        pnode = pnode->next;
        ind++;
    }
    LNode* pn2 = pnode->next;
    if(ind != i)
        return FALSE;
    LNode* ps;
    ps = (LNode*)malloc(sizeof(LNode));
    if(ps == NULL)
        return FALSE;
    pnode->next = ps;
    ps->prior = pnode;
    ps->next = pn2;
    if(pn2 != NULL)
        pn2->prior = ps;
    return OK;
}

//在p结点前插入s结点
Status ListInsertPrior_L(LinkList &L, int i, ElemType e) {
    LNode* pnode = L;
    if(L == NULL)
        return FALSE;
    int ind = 0;
    while(ind != i) {
        pnode = pnode->next;
        ind++;
    }
    if(ind != i)
        return FALSE;
    LNode* pn2 = pnode->prior;
    LNode* ps;
    ps = (LNode*)malloc(sizeof(LNode));
    if(ps == NULL)
        return FALSE;
    pn2->next = ps;
    ps->prior = pn2;
    ps->next = pnode;
    pnode->prior = ps;
    return OK;
}

//删除p结点的直接后继节点
Status ListDeleteNext_L(LinkList &L, int i, ElemType &e) {
    LNode *pnode = L;
    if(L == NULL)
        return FALSE;
    int ind = 0;
    while(ind != i && pnode->next != NULL)
        pnode = pnode->next;
    if(ind != i || pnode->next == NULL)
        return FALSE;
    LNode *ptmp = pnode->next;
    pnode->next = pnode->next->next;
    if(pnode->next != NULL) {
        pnode->next->prior = pnode;
        e = ptmp->data;
        free(ptmp);
    }
    return OK;
}

//在链表中删除第i个结点的前驱
Status ListDeletePrior_L(LinkList &L, int i, ElemType &e) {
    LNode *pnode = L;
    if(L == NULL)
        return FALSE;
    int ind = 0;
    while(ind != i && pnode->next != NULL)
        pnode = pnode->next;
    if(ind != i)
        return FALSE;
    LNode *ptmp = pnode->prior;
    pnode->prior = pnode->prior->prior;
    pnode->prior->next = pnode;
    e = ptmp->data;
    free(ptmp);
    return OK;
}

//在链表中删除第i个结点
Status ListDeleteFront_L(LinkList &L, int i, ElemType &e) {
    LNode *pnode = L;
    if(L == NULL)
        return FALSE;
    int ind = 0;
    while(ind != i && pnode->next != NULL)
        pnode = pnode->next;
    if(ind != i)
        return FALSE;
    e = pnode->data;
    free(pnode);
    return OK;
}

//返回链表中结点个数
int ListLength_L(LinkList L) {
    if(L == NULL) {
        printf("LinkList is Empty\n");
        exit(OVERFLOW);
    }
    LNode* pnode = L->next;
    int cnt = 0;
    while(pnode != NULL) {
        cnt++;
        pnode = pnode->next;
    }
    return cnt;
}

//T6.有头结点单链表
Status ListDeleteRear_L(LinkList &L, int k, ElemType &e) {
    LNode* pnode = L->next;
    if(L == NULL)
        return FALSE;
    if(k<=0 || k>=ListLength_L(L)+1)
        return FALSE;
    for(int j = 1; j < ListLength_L(L)-k-1; j++) {
        pnode = pnode->next;
    }
    LNode *ptmp = pnode->next;
    pnode->next = ptmp->next;
    free(ptmp);
    return TRUE;
}

//T7.检测单链表上是否有环
Status RingExists(LinkList L) {
    LNode *pnode = L;
    LinkList *PreNodes = (LinkList*)malloc(ListLength_L(L) * sizeof(LinkList));
    for(int i = 0; i < ListLength_L(L); i++) {
        PreNodes[i] = pnode;
        for(int j = 0; j < i; j++) {
            if(PreNodes[j] == pnode) {
                return TRUE;
            }
        }
        pnode = pnode->next;
    }
    free(PreNodes);
    return FALSE;
}

