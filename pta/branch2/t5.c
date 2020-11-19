#include<stdio.h>
int fastpow(int base,int power) {
    long long result=1;
    while(power) {
    if(power&1) result*=base;
    power>>=1;
    base=1ll*base*base;
    }
    return result;
}
int evaluation(int n,int a) {
    if(n==-1) return 1;
    return evaluation(n-1,a)+fastpow(a,n+1);
}
int main()
{
       int        n , a ; 

       scanf("%d%d",&n,&a);       
       printf("%d\n",evaluation(n,a));

    return 0;
}