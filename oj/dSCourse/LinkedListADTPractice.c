#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "LinkedListADTPractice.h"

void InitializeList(List* plist) {
    // *plist=NULL;
    *plist=NULL;
    // printf("plist = %p\n",plist);
}

bool ListIsEmpty(const List* plist) {
    if (*plist==NULL) return true;
    else return false;
}

bool ListIsFull(const List* plist) {
    Node* pnew=(Node*)malloc(sizeof(Node));
    if(pnew==NULL) return true;
    else {
        free(pnew);
        return false;
    }
}

unsigned int ListItemCount(const List* plist) {
    int count=0;
    Node* pnow=*plist;
    while(pnow != NULL) {
        count++;
        pnow=pnow->next;
    }
    return count;
}

bool AddItem(Item item,List* plist) {
    Node* pnew=(Node*)malloc(sizeof(Node));
    if(pnew==NULL) return false;

    pnew->item=item;
    pnew->next=NULL;

    Node* pnode=*plist;

    if(pnode==NULL)
        *plist=pnew;//Fuck!!!!!!!
    else {
        while(pnode->next != NULL)
            pnode=pnode->next;
        pnode->next=pnew;
    }
    // printf("*plist = %p, (*plist)->next = %p\n",*plist,(*plist)->next);
    // printf("pnew = %p, pnode = %p, pnode->next = %p\n",pnew,pnode,pnode->next);

    return true;
}

void Traverse(const List* plist,void (*pfun)(Item item)) {
    Node* pnode = *plist;
    while(pnode != NULL) {
        (*pfun)(pnode->item);
        pnode=pnode->next;
    }
}

void EmptyTheList(List* plist) {
    Node* pnode=*plist;
    while(pnode != NULL) {
        Node* pnext=pnode->next;
        free(pnode);
        pnode=pnext;
    }
}