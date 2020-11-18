#include<stdio.h>
int mypow(int x,int n) {
    long long result=1;
    while(n) {
        if(n&1) result*=x;
        n>>=1;
        x=1ll*x*x;
    }
    return result;
}

int main()
{
    int x, n ;

    scanf("%d%d",&x,&n) ;
    printf("%d\n",mypow(x,n)) ;

    return 0;
}
