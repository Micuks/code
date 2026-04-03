#include<stdio.h>
void sort(int *a,int *b,int *c) {
    if(*a>*b) {
        *a+=*b;
        *b=*a-*b;
        *a-=*b;
    }
    if(*b>*c) {
        *b+=*c;
        *c=*b-*c;
        *b-=*c;
    }
    if(*a>*c) {
        *a+=*c;
        *c=*a-*c;
        *a-=*c;
    }
}
int judgeTriangle(int a,int b,int c) {
    sort(&a,&b,&c);
    //printf("a = %d,b = %d,c = %d\n",a,b,c);
    if(a<1||b<1||c<1||a+b<=c) return -1;
    else if(1ll*a*a+1ll*b*b-1ll*c*c==0) return 1;
    else if(a==c) return 3;
    else if(a==b||b==c) return 2;
    else return 0;
}

int judgeTriangle1(int a,int b,int c) {
    // sort(&a,&b,&c);
    if(a>0 && b>0 && c>0 && a+b>c && a+c>b && b+c>a)
    {
        if(a==b && b==c) return 3;
        else if(a==b || a==c || b==c) return 2;
        else if(a*a+b*b==c*c || a*a+c*c==b*b || b*b+c*c==a*a) return 1;
        else return 0;
    }
    else return -1;
}

int main()
{
    int        a, b, c ;    

    scanf("%d%d%d",&a,&b,&c);

    switch(judgeTriangle(a,b,c))
    {
        case    -1    :    printf("It is not a triangle.\n") ;    break ;
        case    0    :    printf("It is a scalenous triangle.\n") ;    break ;
        case    1    :    printf("It is a right-angled triangle.\n") ;    break ;
        case    2    :    printf("It is an isosceles triangle.\n") ;    break ;
        case    3    :    printf("It is a equilateral triangle.\n") ;    break ;
    }

    return 0;
}