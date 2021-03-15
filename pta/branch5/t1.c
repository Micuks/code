#include <stdio.h>

typedef struct
{
    char id[16]; //学生账号
    int total;   //综合成绩
    int ce;      //机试成绩
    int ws;      //加权成绩
} STUDENT;

void Sort(STUDENT a[], int size);
void Swap(STUDENT *s1, STUDENT *s2);
int Comp(STUDENT *s1, STUDENT *s2);

int main()
{
    STUDENT stu[100];
    int i, n;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%s%d%d", stu[i].id, &stu[i].ce, &stu[i].ws);
        stu[i].total = stu[i].ce + stu[i].ws;
    }

    Sort(stu, n);
    for (i = 0; i < n; i++)
        printf("%s %d %d %d\n", stu[i].id, stu[i].total, stu[i].ce, stu[i].ws);

    return 0;
}
void Swap(STUDENT* s1,STUDENT* s2) {
    int temp;
    temp=s1->ce;
    s1->ce=s2->ce;
    s2->ce=temp;
    char ch;
    for(int i=0;i<16;i++) {
        ch=s1->id[i];
        s1->id[i]=s2->id[i];
        s2->id[i]=ch;
    }
    temp=s1->total;
    s1->total=s2->total;
    s2->total=temp;
    temp=s1->ws;
    s1->ws=s2->ws;
    s2->ws=temp;
}
int Comp(STUDENT* s1,STUDENT* s2) {
    if(s1->total>s2->total) return 1;
    else if(s1->total==s2->total) {
        if(s1->ce>s2->ce) return 1;
    }
    return 0;
}
void Sort(STUDENT a[],int size) {
    for(int i=0;i<size;i++) {
        for(int j=size-1;j>i;j--) {
            if(Comp(a+j,a+j-1)) Swap(a+j,a+j-1);
        }
    }
}