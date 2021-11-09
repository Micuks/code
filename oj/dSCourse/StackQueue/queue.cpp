#include <cstdio>
#include <cstdlib>
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define Status int

typedef int ElemType;
typedef struct NODE {
    ElemType val;
    struct NODE* next;
} Node;

typedef struct QUEUE {
    Node* rear;
} Queue;

Status InitQueue(Queue &q) {
    q.rear = (Node*)malloc(sizeof(Node));
    if(q.rear == NULL)
        exit(OVERFLOW);
    q.rear->next = q.rear;
    return TRUE;
}

Status EnQueue(Queue &q, ElemType e) {
    Node* pnode = (Node*)malloc(sizeof(Node));
    if(pnode == NULL)
        exit(OVERFLOW);
    pnode->val = e;
    pnode->next = q.rear->next;
    q.rear->next = pnode;
    q.rear = pnode;
    return TRUE;
}

Status DeQueue(Queue &q, ElemType &e) {
    if(q.rear == NULL)
        exit(OVERFLOW);
    if(q.rear->next == q.rear)
        printf("rear = head\n");
    e = q.rear->next->next->val;
    Node* ptmp = q.rear->next->next;
    q.rear->next->next = ptmp->next;
    free(ptmp);
    return TRUE;
}

int main() {
    Queue que;
    InitQueue(que);
    EnQueue(que, 123);
    ElemType elem = 0;
    DeQueue(que, elem);
    printf("%d\n", elem);
    return 0;
}
