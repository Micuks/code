#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OVERFLOW -2
#define INT_MIN -2147483648

typedef struct node{
   int coef, exp;
   struct node *next;
} *poly, node;

/* 从字符串创建带头结点链表形式的多项式,
降次排列, 字符串格式为5x2+3x1+1x0 */
poly CreatPoly(char* str)
{
   poly head;
   head = (poly)malloc(sizeof(node));
   if(head == NULL) {
       printf("Failed to allocate space for head.\n");
       exit(OVERFLOW);
   }
   head->next = NULL;
   head->exp = INT_MIN;
   int tmp;
   node* s, *ppre = head;
   s = (node*)malloc(sizeof(node));
   s->next = NULL;
   for(int i = 0; i < strlen(str); i++) {
       if(i == 0) {
           sscanf(str, "%d", &tmp);
           //printf(" coef = %d\n", tmp);
           s->coef = tmp;
       }
       else if(str[i] == 'x') {
           //printf(" x %s\n", str+i);
           sscanf(str+i+1, "%d", &tmp);
           //printf("exp = %d\n", tmp);
           s->exp = tmp;
           ppre->next = s;
           ppre = s;
           s = (node*)malloc(sizeof(node));
           s->next = NULL;
       }
       else if(str[i-1] != 'x' && (str[i] == '+' || str[i] == '-')) {
           //printf(" %s\n", str+i);
           if(str[i] == '+') {
               sscanf(str+i+1, "%d", &tmp);
           }
           else {
               sscanf(str+i, "%d", &tmp);
           }
           //printf(" coef = %d\n", tmp);
           s->coef = tmp;
       }
   }
   // Your code here

   return head;
}

/* 释放链表的空间 */
void DelPoly(poly p)
{
   poly oldhead;
   poly temp=p->next;
   while(temp!=NULL)
   {
   	oldhead=temp;
   	temp=oldhead->next;
   	free(oldhead);
   }

   // Your code here
}

/* 新建带头结点链表形式的多项式,
存储a+b的结果, 并返回头指针 */
poly AddPoly(poly a,poly b)
{
   poly head;
   head=a;
   node*p,*q,*u,*pre;
   p=a->next;
   q=b->next;
   pre=a;
   while((p!=NULL)&&q!=NULL)
   {
   	if(p->exp>q->exp)
   	{
   		pre=p;
   		p=p->next;
	   }
	   else if(p->exp==q->exp)
	   {
	   	float x;
	   	x=p->coef+q->coef;
	   	if(x!=0)
	   	{
	   		p->coef=x;
	   		pre=p;
		   }
		   else{
		   	pre->next=p->next;
		   	free(p);
		   }
		   p=pre->next;
		   u=q;
		   q=q->next;
		   free(u);
	   }
	   else if(p->exp<q->exp)
	   {
	   	u=q->next;
	   	q->next=p;
	   	pre->next=q;
	   	pre=q;q=u;
	   }
   }
   if(q!=NULL)
   {
   	pre->next=q;
   }
   
   // Your code here

   return head;
}

/* 新建带头结点链表形式的多项式,
存储a*b的结果, 并返回头指针 */
poly MulPoly(poly a,poly b)
{
    poly head = (poly)malloc(sizeof(node));
    head->exp = INT_MIN;
    head->next = NULL;
    if(a->next == NULL || b->next == NULL) {
        printf("a == NULL || b == NULL!!\n");
        return NULL;
    }
    node *p1 = a->next, *p2 = b->next, *p3 = head;
    while(p1 != NULL) {
        p2 = b->next;
        while(p2 != NULL) {
            int coef = p1->coef * p2->coef;
            int exp = p1->exp + p2->exp;
            p3 = head;
            while(p3->next != NULL && p3->next->exp > exp) {
                p3 = p3->next;
            }
            if(p3->next != NULL && p3->next->exp == exp) {
                p3->next->coef += coef;
            }
            else {
                node* s = (node*)malloc(sizeof(node));
                s->next = NULL;
                s->exp = exp;
                s->coef = coef;
                p3->next = s;
            }
            p2 = p2->next;
        }
        p1 = p1->next;
    }
   // Your code here
    return head;
}

/* 输出多项式 */
void Output(poly c)
{
   // Your code here
   poly p;
   p=c->next;
   printf("%dx%d", p->coef, p->exp);
   while(p->next!=NULL)
   {
       p = p->next;
       if(p->coef >= 0) {
           printf("+%dx%d",p->coef,p->exp);
       }
       else {
           printf("%dx%d",p->coef,p->exp);
       }
   }
   putchar('\n');
}

int main()
{
   poly a, b, c;
   char str1[64], str2[64];

   printf("Please input polynomial A: ");
   scanf("%s", str1);
   printf("Please input polynomial B: ");
   scanf("%s", str2);
   //printf("%s\n%s\n", str1, str2);
   
   a = CreatPoly(str1);
   b = CreatPoly(str2);

   Output(a);
   Output(b);

   c = MulPoly(a,b);
   //printf("The result of A times B is: ");
   Output(c);

   DelPoly(a);
   DelPoly(b);
   DelPoly(c);

   return 0;   
}

