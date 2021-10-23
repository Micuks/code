#include <stdio.h>
#include <stdlib.h>
#include "LinkList.hpp"

Status CreatePolyn(Polynomial &p);

Status PrintPolyn(Polynomial p);

Status AddPolyn(Polynomial pa, Polynomial pb, Polynomial &pc);

Status MinusPolyn(Polynomial pa, Polynomial pb, Polynomial &pc);

int main() {
    Polynomial Pa, Pb, Pc;
    InitList_L(Pa);
    InitList_L(Pb);
    InitList_L(Pc);
    printf("Input a polynomial.");
    CreatePolyn(Pa);
    printf("Input 1: Display the polynomial.\n"
            "Input 2: Input another polynomial\n"
            "Input 0: Quit.\n");
    int kase = 0;
    scanf("%d", &kase);
    while(kase != 0) {
        if(Pb->next == NULL) {
            printf("Input 1: Display the polynomial.\n"
                    "Input 2: Input another polynomial\n");
            scanf("%d", &kase);
            if(kase == 1) {
                PrintPolyn(Pa);
            }
            else if(kase == 2) {
                CreatePolyn(Pb);
            }
        }
        else {
            printf("Input 1: Display the polynomials.\n"
                    "Input 2: Output the sum of two polynomials.\n"
                    "Input 3: Output the result of Polynomial A - Polynomial B\n");
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
        printf("Input 0 to quit.\n"
                "Or Input 1 to continue.\n");
        scanf("%d", &kase);
    }
}

Status CreatePolyn(Polynomial &p) {
    LNode* pnode;
    AllocateNode(pnode);
}
