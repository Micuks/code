#include "../include/tree.h"

Status InitBiTree(BiTree &T) { /* 操作结果: 构造空二叉树T */
    T = NULL;
    return OK;
}

void DestroyTree(BiTree &T) {
    if(T) {
        if(T->lch)
            DestroyTree(T->lch);
        if(T->rch)
            DestroyTree(T->rch);
        free(T);
        T = NULL;
    }
}

Status CreateBiTree(BiTree &T) {
    datatype ch;
    scanf("%c", &ch);
    if(ch == Nil)
        T = NULL;
    else {
        T = (BiTNode *)malloc(sizeof(BiTNode));
        if(!T) {
            printf("FAILED TO MALLOC!!!\n");
            exit(OVERFLOW);
        }
        T->data = ch;
        CreateBiTree(T->lch);
        CreateBiTree(T->rch);
    }
    return OK;
}

int PostOrderBiTreeDepth(BiTree T) {
    int i = 0, j = 0;
    if(T->lch) {
        i = PostOrderBiTreeDepth(T->lch);
    }
    if(T->rch) {
        j = PostOrderBiTreeDepth(T->rch);
    }
    if(!T) {
        return 0;
    }
    return i > j ? i+1 : j+1;
}

int PreOrderBiTreeDepth(BiTree T) {
    int i = 0, j = 0;
    if(!T)
        return 0;
    if(T->lch)
        i = PreOrderBiTreeDepth(T->lch);
    if(T->rch)
        j = PreOrderBiTreeDepth(T->rch);
    return i > j ? i+1 : j+1;
}

int PreOrderBiTreeCount(BiTree T) {
    int num = 1;
    if(!T)
        return 0;
    if(T->lch)
        num += PreOrderBiTreeCount(T->lch);
    if(T->rch)
        num += PreOrderBiTreeCount(T->rch);
    return num;
}

void CountDescNum(BiTree T) {
    Stack s;
    InitStack(&s);
    BiTNode *cur = T, *pre = NULL;
    while(cur || !StackEmpty(&s)) {
        while(cur) {
            push(cur, &s);
            cur = cur->lch;
        }
        top(cur, &s);
        if(cur->rch == NULL || pre == cur->rch) {
            cur->descnum = 0;
            if(cur->lch) {
                cur->descnum += cur->lch->descnum + 1;
            }
            if(cur->rch) {
                cur->descnum += cur->rch->descnum + 1;
            }
            pre = cur;
            pop(cur, &s);
            cur = NULL;
        }
        else {
            cur = cur->rch;
        }
    }
}

int CountLeaves(Tree T) {
    int cnt = 1;
    if(T->lchild == NULL)
        return cnt;
    cnt += CountLeaves(T->lchild);
    SNode* ptree = T->lchild;
    while(ptree->nextsibling) {
        ptree = ptree->nextsibling;
        cnt += CountLeaves(ptree);
    }
    return cnt;
}

int CountDegree(Tree T) {
    int i = 0, j = 0, max = -1, tmp;
    SNode *q[MAXN];
    if(T) {
        max = 0;
        q[j++] = T->lchild;
        while(i < j) {
            tmp = 0;
            while(q[i]) {
                tmp++;
                if(q[i]->lchild) {
                    q[j++] = q[i]->lchild;
                }
                q[i] = q[i]->nextsibling;
            }
            max = (max >= tmp)? max : tmp;
            i++;
        }
    }
    return max;
}

Status visitT(datatype e) {
    printf("%c ",e);
    return OK;
}

int main(int argc, char* argv[])
{
    BiTree T;
    InitBiTree(T);
    printf("请先序输入二叉树(如:ABD0G000CE00F00)\n");

    CreateBiTree(T);

    int depth=PostOrderBiTreeDepth(T);
    printf("二叉树的深度为：%d\n",depth);    //输出深度 

    int countleaf=PreOrderBiTreeCount(T);
    printf("叶子结点的数目为：%d\n",countleaf); 

    DestroyTree(T);

    return 0;
}
