#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void InitializeQueue(Queue* pq) {
    pq->front=NULL;
    pq->rear=NULL;
    pq->items=0;
}

bool QueueIsFull(Queue* pq) {
    return pq->items == MAXQUEUE;
}

bool QueueIsEmpty(Queue* pq) {
    return pq->items == 0;
}

int QueueItemCount(Queue* pq) {
    return pq->items;
}

bool EnQueue(Item item,Queue* pq) {
    Node* pnew = (Node*)malloc(sizeof(Node));
    if(pnew == NULL) {
        fprintf(stderr,"Failed to allocate memory!\n");
        exit(1);
    }
    pnew->item = item;
    pnew->next = NULL;

    if(QueueIsFull(pq)==true) {
        fprintf(stderr,"Queue is full.");
        return false;
    }
    if(QueueIsEmpty(pq)==true) {
        pq->front = pnew;
        pq->rear = pnew;
        pq->items = 1;
    }
    else {
        pq->rear->next = pnew;
        pq->rear = pnew;
        pq->items++;
    }

    return true;
}

bool DeQueue(Item* pitem,Queue* pq) {
    if(pitem == NULL) {
        fprintf(stderr,"The container is NULL.");
        return false;
    }
    if(QueueIsEmpty(pq) == true) {
        printf(stderr,"Queue is empty! Failed to deque!");
        return false;
    }
    if(QueueItemCount(pq) == 1) {
        pitem = pq->front->item;
        free(pq->front);
        InitializeQueue(pq);
    }
    else {
        pitem = pq->front->item;
        Node* pnode = pq->front->next;
        free(pq->front);
        pq->front = pnode;
        pq->items--;
    }
    return true;
}

bool EmptyTheQueue(Queue* pq) {
    if(pq == NULL) {
        fprintf(stderr,"The queue doesn't exist!");
        return false;
    }
    if(QueueIsEmpty(pq) == true) {
        fprintf(stderr,"The queue is empty!");
        return false;
    }
    while(QueueIsEmpty(pq) == false) {
    Node* pnow=pq->front->next;
        free(pq->front);
        pq->front = pnow;
        pq->items--;
    }
    InitializeQueue(pq);
    return true;
}