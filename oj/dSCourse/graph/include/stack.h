#include <cstring>
#include <cstdio>
#include <cstdlib>

#define TRUE 1
#define FALSE 0
const int MAXN = 1000;

typedef int VertexType;
typedef VertexType elemtype;

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
