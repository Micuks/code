#include "../include/stack.h"

int GetNum(char* str);

bool InitStack(Stack* pstack) {
    pstack->front = NULL;
    pstack->num = 0;
    pstack->rear = NULL;
    return 1;
}

bool push(elemtype* pnum, Stack* pstack) {
    Node* pnode = (Node*)malloc(sizeof(Node));
    if(pnode == NULL) {
        printf("!! Failed to malloc a memory for new node !!\n");
        return FALSE;
    }
    pnode->val = *pnum;
    if(pstack->num == 0) {
        pnode->previous = NULL;
        pstack->front = pnode;
    }
    else {
        pnode->previous = pstack->rear;
        pstack->rear = pnode;
    }
    pstack->num++;
    return TRUE;
}

bool pop(elemtype* pnum, Stack* pstack) {
    if(pstack->num == 0) {
        printf("!! There's no nodes in stack !!\n");
        return FALSE;
    }
    *pnum = pstack->rear->val;
    if(pstack->num == 1) {
        free(pstack->front);
        pstack->front = NULL;
        pstack->rear = NULL;
    }
    else {
        Node* pnode = pstack->rear;
        pstack->rear = pstack->rear->previous;
        free(pnode);
    }
    pstack->num--;
    return TRUE;
}

bool top(elemtype *pnum, Stack *pstack) {
    if(pstack->rear == NULL) {
        printf("!! There's no nodes in stack !!\n");
        return FALSE;
    }
    *pnum = pstack->rear->val;
    return TRUE;
}

int HowManyNodesInTheStack(Stack* pstack) {
    return pstack->num;
}

bool ReleaseStack(Stack* pstack) {
    while(pstack->num) {
        elemtype tmp;
        pop(&tmp, pstack);
    }
    free(pstack);
    return 0;
}

int GetNum(char* str) {
    int len=strlen(str);
    int result = 0;
    for(int i=0;i<len;i++) {
        if((str[i] - '0') >= 0 && ('9' - str[i]) >= 0) {
            result *= 10;
            result += str[i] - '0';
        }
    }
//    printf("result = %d\n",result);
    return result;
}

bool StackEmpty(Stack *ps) {
    if(ps->num == 0)
        return TRUE;
    else return FALSE;
}
