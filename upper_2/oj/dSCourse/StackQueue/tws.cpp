#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;
#define TRUE 1
#define FALSE 0
#define STACK_INIT_SIZE 1000
#define STACKINCREMENT 100
#define OVERFLOW -2
typedef int Status;
typedef int Elemtype;
typedef struct {
    Elemtype *top0;
    Elemtype *top1;
    Elemtype *base;
    int stacksize;
} SqStack;

void ERROR(string str) {
    cout << str;
    exit(OVERFLOW);
}

Status InitStack(SqStack &tws) {
    tws.base = (Elemtype*)malloc(STACK_INIT_SIZE * sizeof(Elemtype));
    if(tws.base == NULL)
        ERROR("FAILED TO ALLOCATE SPACE.\n");
    tws.top0 = tws.base;
    tws.top1 = tws.base + STACK_INIT_SIZE - 1;
    tws.stacksize = STACK_INIT_SIZE;
    return TRUE;
}

Status push(SqStack &tws, int i, Elemtype e) {
    if(tws.base == NULL)
        ERROR("OVERFLOW\n");
    if(tws.top0 + 1 == tws.top1)
        ERROR("OVERFLOW\n");
    if(i == 0) {
        *tws.top0++ = e;
        //printf("tws.top0-1 = %d\n", *(tws.top0 - 1));
    }
    else if(i == 1) {
        *tws.top1-- = e;
        //printf("tws.top1+1 = %d\n", *(tws.top1 + 1));
    }
    return TRUE;
}

Status pop(SqStack &tws, int i, Elemtype &e) {
    if(tws.base == NULL)
        ERROR("OVERFLOW\n");
    if(i == 0) {
        if(tws.base == tws.top0)
            ERROR("Stack is empty!\n");
        e = *--tws.top0;
    }
    else if(i == 1) {
        if(tws.top1 == tws.base + STACK_INIT_SIZE - 1)
            ERROR("Stack is empty!\n");
        e = *++tws.top1;
    }
    return TRUE;
}
int main() {
    SqStack tws;
    InitStack(tws);
    push(tws, 0, 233);
    push(tws, 1, 345);
    Elemtype e;
    pop(tws, 0, e);
    printf("%d\n", e);
    pop(tws, 1, e);
    printf("%d\n", e);
    return 0;
}
