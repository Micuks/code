#include <stdio.h>
#include <stdlib.h>
#include "../include/LinkList.hpp"

const float eps = 1e-6;

//创建多项式
Status CreatePolyn(Polynomial &p);

//打印多项式
Status PrintPolyn(Polynomial p);

//多项式相加输出到pc
Status AddPolyn(Polynomial pa, Polynomial pb, Polynomial &pc);

//多项式相减输出到pc
Status MinusPolyn(Polynomial pa, Polynomial pb, Polynomial &pc);

//多项式求导
Status DerivativePolyn(Polynomial &p);

int main() {
    Polynomial Pa, Pb, Pc;
    InitList_L(Pa);
    InitList_L(Pb);
    InitList_L(Pc);
    printf("Input a polynomial.");
    CreatePolyn(Pa);
    int kase = 0;
    while(kase != 0) {
        if(Pb->next == NULL) {
            printf("Input 1: Display the polynomial.\n"
                    "Input 2: Input another polynomial\n"
                    "Input 3: Derivate the polynomial.\n"
                    "Input 0: Quit.\n");
            scanf("%d", &kase);
            switch(kase) {
                case 1:
                    PrintPolyn(Pa);
                    break;
                case 2:
                    CreatePolyn(Pb);
                    break;
                case 3:
                    DerivativePolyn(Pa);
            }
        }
        else {
            printf("Input 1: Display the polynomials.\n"
                    "Input 2: Output the sum of two polynomials.\n"
                    "Input 3: Output the result of Polynomial A - Polynomial B.\n"
                    "Input 0: Quit.\n");
            scanf("%d", &kase);
            switch(kase) {
                case 1:
                    PrintPolyn(Pa);
                    PrintPolyn(Pb);
                    break;
                case 2:
                    AddPolyn(Pa, Pb, Pc);
                    PrintPolyn(Pc);
                    break;
                case 3:
                    MinusPolyn(Pa, Pb, Pc);
                    PrintPolyn(Pc);
                    break;
                default:
                    break;
            }
        }
    }
}

//创建多项式
Status CreatePolyn(Polynomial &p) {
    InitList_L(p);
    LNode* pnode = p;
    ElemType newelem;
    int n;
    scanf("%d", &n);
    if(n <= 0) {
        printf("n <= 0!!!");
        return FALSE;
    }
    for(int i = 0; i < n; i++) {
        int c, e;
        scanf("%d%d", &c, &e);
        newelem.coef = c;
        newelem.expn = e;
        for(int j = 0; j < ListLength_L(p); j++) {
            if(pnode->data.expn > newelem.expn) {
                ListInsertPrior_L(p, j, newelem);
                break;
            }
        }
    }
    return TRUE;
}

//打印多项式
Status PrintPolyn(Polynomial p) {
    LNode *pnode = p->next;
    if(pnode == NULL)
        return FALSE;
    int sum = ListLength_L(p);
    printf("%d ", sum);
    for(int i = 0; i < sum; i++) {
        printf("c%d: %f, e%d: %d, ", i, pnode->data.coef, i, pnode->data.expn);
    }
    return TRUE;
}

//比较pa和pb的指数大小
int compare(Polynomial pa, Polynomial pb) {
    if(pa->data.expn < pb->data.expn)
        return -1;
    else if(pa->data.expn == pb->data.expn)
        return 0;
    else if(pa->data.expn > pb->data.expn)
        return 1;
    return -2;
}

//多项式相加输出到pc
Status AddPolyn(Polynomial pa, Polynomial pb, Polynomial &pc) {
    LNode *p1 = pa, *p2 = pb;
    while(pa != NULL || pb != NULL) {
        switch(compare(p1, p2)) {
            case -1:
                AddElem_L(pc, p1->data);
                p1 = p1->next;
                break;
            case 0:
                ElemType newelem;
                newelem.expn = p1->data.expn;
                newelem.coef = p1->data.coef + p2->data.coef;
                if(newelem.coef < eps)
                    newelem.coef = 0;
                AddElem_L(pc, newelem);
                p1 = p1->next;
                p2 = p2->next;
                break;
            case 1:
                AddElem_L(pc, p2->data);
                p2 = p2->next;
                break;
            default:
                break;
        }
    }
    return TRUE;
}

//多项式相减输出到pc
Status MinusPolyn(Polynomial pa, Polynomial pb, Polynomial &pc) {
    LNode *p1 = pa, *p2 = pb;
    while(pa != NULL || pb != NULL) {
        switch(compare(p1, p2)) {
            case -1:
                AddElem_L(pc, p1->data);
                p1 = p1->next;
                break;
            case 0:
                ElemType newelem;
                newelem.expn = p1->data.expn;
                newelem.coef = p1->data.coef - p2->data.coef;
                if(newelem.coef < eps)
                    newelem.coef = 0;
                AddElem_L(pc, newelem);
                p1 = p1->next;
                p2 = p2->next;
                break;
            case 1:
                AddElem_L(pc, p2->data);
                p2 = p2->next;
                break;
            default:
                break;
        }
    }
    return TRUE;
}

//多项式求导
Status DerivativePolyn(Polynomial &p) {
    LNode* pnode = p->next;
    LNode* ppre = p;
    while(p != NULL) {
        if(pnode->data.expn == 0) {
            LNode* ptmp = pnode;
            ppre->next = pnode->next;
            p->next->prior = ppre;
            free(ptmp);
            pnode = pnode->next;
            ppre = ppre->next;
        }
        else {
            pnode->data.coef = pnode->data.coef + pnode->data.expn;
            pnode->data.expn-=1;
            pnode = pnode->next;
            ppre = ppre->next;
        }
    }
    return TRUE;
}
