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

//multiply
Status MultiplyPolyn(Polynomial pa, Polynomial pb, Polynomial &pc);

int mian() {
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
    return 0;
}

int main() {
    Polynomial pa, pb, pc;
    printf("CreatePolyn-a---%d\n", CreatePolyn(pa));
    printf("CreatePolyn-b---%d\n", CreatePolyn(pb));
    printf("InitList_L-c---%d\n", InitList_L(pc));
    printf("MultiplyPolyn---%d\n", MultiplyPolyn(pa, pb, pc));
    printf("PrintPolyn---%d\n", PrintPolyn(pc));
    return 0;
}

//创建多项式
Status CreatePolyn(Polynomial &p) {
    //printf("InitList---%d\n", InitList_L(p));
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
        pnode = p;
        float c;
        int e;
        scanf("%f%d", &c, &e);
        newelem.coef = c;
        newelem.expn = e;
        //printf("len = %d\n", ListLength_L(p));
        while(pnode != NULL) {
            //printf("pnode->data.expn = %d, newelem.expn = %d\n", pnode->data.expn, newelem.expn);
            if(pnode->next == NULL) {
                AddElem_L(p, newelem);
                //printf("(c,e) = (%.2f, %d), len = %d\n", pnode->next->data.coef, pnode->next->data.expn, ListLength_L(p));
                break;
            }
            else if(pnode->next->data.expn < newelem.expn) {
                AddElemNext_L(pnode, newelem);
                //printf("(c,e) = (%.2f, %d), len = %d\n", newelem.coef, newelem.expn, ListLength_L(p));
                break;
            }
            pnode = pnode->next;
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
        printf("%d: (%.2f, %d), ", i, pnode->data.coef, pnode->data.expn);
        pnode = pnode->next;
    }
    putchar('\n');
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

Status MultiplyPolyn(Polynomial pa, Polynomial pb, Polynomial &pc) {
    InitList_L(pc);
    if(pa->next == NULL || pb->next == NULL)
        return FALSE;
    LNode* p1 = pa->next, *p2 = pb, *p3 = pc;
    printf("Length of a: %d, b: %d\n", ListLength_L(pa), ListLength_L(pb));
    while(p1 != NULL) {
        p2 = pb;
        while(p2 != NULL) {
            ElemType e;
            e.coef = p1->data.coef * p2->data.coef;
            e.expn = p1->data.expn + p2->data.expn;
            p3 = pc;
            while(p3->next != NULL && p3->next->data.expn < e.expn) {
                printf("- ");
                p3 = p3->next;
            }
            printf("p3->next = %p\n", p3->next);
            printf("AddElemNext_L---%d\n", AddElemNext_L(p3, e));
            //AddElemNext_L(p3, e);
            printf("(%.2f, %d)\n", p3->next->data.coef, p3->next->data.expn);
            p2 = p2->next;
        }
        p1 = p1->next;
    }
    return TRUE;
}
