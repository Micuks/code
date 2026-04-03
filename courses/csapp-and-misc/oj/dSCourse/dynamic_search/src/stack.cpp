#include "../include/stack.h"
#include <cstdlib>
#include <cstdio>

bool InitStack(SqStack &S) {
    S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!S.base) {
        printf("failed to allocate memory\n");
        return false;
    }
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return true;
}

bool push(SElemType e, SqStack &S) {
    if(S.top - S.base >= S.stacksize) {
        S.base = (SElemType*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
        if(!S.base) {
            printf("failed to allocate memory\n");
            return false;
        }
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return true;
}

bool pop(SElemType &e, SqStack &S) {
    if(S.top == S.base) {
        printf("stack is empty\n");
        return false;
    }
    e = * --(S.top);
    return true;
}

bool top(SElemType &e, SqStack &S) {
    if(S.top == S.base) {
        printf("stack is empty\n");
        return false;
    }
    e = *(S.top-1);
    return true;
}

int StackLength(SqStack &S) {
    return S.top - S.base;
}

void DestroyStack(SqStack &S) {
    free(S.base);
}

bool StackEmpty(SqStack S) {
    return S.base == S.top;
}
