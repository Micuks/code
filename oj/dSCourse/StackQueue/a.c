#include <stdio.h>
#include <stdlib.h>
#define QueueSize 100
typedef char DataType;
typedef struct {
    int front;
    int rear;
    int count;
    DataType data[QueueSize];
} CirQueue;

void Error(char *str) {
    printf("%s\n", str);
    exit(-1);
}

void InitQueue(CirQueue *Q) {
    Q->front = Q->rear = 0;
    Q->front = 5;
    Q->count = 0;
}

int QueueEmpty(CirQueue *Q) {
    if(Q->rear - 1 == Q->front || (Q->front == QueueSize - 1 && Q->rear == 0))
        return 1;
    return 0;
}

//根据front与rear相等前的大小关系判断队列是否已满
int QueueFull(CirQueue *Q) {
    if(Q->front - 1 == Q->rear || (Q->rear == QueueSize-1 && Q->front == 0))
        return 1;
    return 0;
}

void EnQueue(CirQueue *Q, DataType x) {
    if(QueueFull(Q))
        Error("Queue overflow");
    Q->count++;
    Q->data[Q->rear] = x;
    Q->rear = (Q->rear + 1) % QueueSize;
}

DataType DeQueue(CirQueue *Q) {
    DataType temp;
    if(QueueEmpty(Q))
        Error("Queue underflow");
    temp = Q->data[Q->front];
    Q->count--;
    Q->front = (Q->front + 1) % QueueSize;
    return temp;
}

DataType QueueFront(CirQueue *Q) {
    if(QueueEmpty(Q))
        Error("Queue if empty.");
    return Q->data[Q->front];
}
