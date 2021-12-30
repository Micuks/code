#include "common.h"

const int MAXN = 1000;

typedef struct node {
    BiTNode elem;
    struct node* previous;
} Node;

typedef struct list {
    Node* front;
    Node* rear;
    int num;
} List;

typedef List Stack;

bool InitStack(Stack* ps);

bool push(BiTNode* pelem, Stack* pstack);

bool pop(BiTNode* pelem, Stack* pstack);

bool top(BiTNode* pelem, Stack* pstack);

int HowManyNodesInTheStack(Stack* pstack);

bool ReleaseStack(Stack* pstack);

//int GetNum(char* str);

bool StackEmpty(Stack* ps);
