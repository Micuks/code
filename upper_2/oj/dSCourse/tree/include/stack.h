#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "common.h"

const int MAXN = 1000;

typedef BiTNode elemtype;

typedef struct node {
    elemtype val;
    struct node* previous;
} Node;

typedef struct list {
    Node* front;
    Node* rear;
    int num;
} List;

typedef List Stack;

bool InitStack(Stack* ps);

bool push(elemtype* pnum, Stack* pstack);

bool pop(elemtype* pnum, Stack* pstack);

bool top(elemtype* pnum, Stack* pstack);

int HowManyNodesInTheStack(Stack* pstack);

bool ReleaseStack(Stack* pstack);

int GetNum(char* str);

bool StackEmpty(Stack* ps);
