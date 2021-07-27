#include <cstdbool>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int MAXN=1000;

typedef struct node {
    int val;
    struct node* previous;
} Node;

typedef struct list {
    Node* front;
    Node* rear;
    int num;
} List;

typedef List Stack;

bool InitStack(Stack* pstack);
bool push(int* pnum, Stack* pstack);
bool pop(int* pnum, Stack* pstack);
int HowManyNodesInTheStack(Stack* pstack);
bool ReleaseStack(Stack* pstack);
int GetNum(char* str);

int main() {
    int flag = 1;
    char str[MAXN];
    Stack sta;
    InitStack(&sta);
//    scanf("%s",str);
//    printf("str = %s ",str);
    while(scanf("%s",str) == 1) {
        int num = GetNum(str);
        if(str[1] == 'u') {
            push(&num, &sta);
        }
        else if(str[1] == 'o') {
            pop(&num, &sta);
            if(flag) {
                printf("%d", num);
                flag=0;
            }
            else printf(", %d", num);
        }
//        printf("str = %s, %d\n", str, scanf("%s",str));
    }
    return 0;
}

bool InitStack(Stack* pstack) {
    pstack->front = NULL;
    pstack->num = 0;
    pstack->rear = NULL;
    return 1;
}

bool push(int* pnum, Stack* pstack) {
    Node* pnode = (Node*)malloc(sizeof(Node));
    if(pnode == NULL) {
        printf("!! Failed to malloc a memory for new node !!\n");
        return 1;
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
    return 0;
}

bool pop(int* pnum, Stack* pstack) {
    if(pstack->num == 0) {
        printf("!! There's no nodes in stack !!");
        return 1;
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
    return 0;
}

int HowManyNodesInTheStack(Stack* pstack) {
    return pstack->num;
}

bool ReleaseStack(Stack* pstack) {
    while(pstack->num) {
        int tmp;
        pop(&tmp, pstack);
    }
    free(pstack);
    return 0;
}

int GetNum(char* str) {
    char tmp;
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
