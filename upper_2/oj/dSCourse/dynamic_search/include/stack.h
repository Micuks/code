#include "common.h"

const int STACK_INIT_SIZE = 1024;
const int STACKINCREMENT = 256;

typedef BiTNode* SElemType;

typedef struct {
    SElemType *base;
    SElemType *top;
    int stacksize;
} SqStack;

bool InitStack(SqStack &S);

bool push(SElemType e, SqStack &S);

bool pop(SElemType &e, SqStack &S);

bool top(SElemType &e, SqStack &S);

int StackLength(SqStack S);

void DestroyStack(SqStack &S);

bool StackEmpty(SqStack S);
