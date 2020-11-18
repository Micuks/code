#include<stdio.h>
int getDigit(long long n) {
    if(n<10) return 1;
    else return getDigit(n/10)+1;
}
int main()
{
    long long     n ;
    int            len ;

    scanf("%lld",&n);
    len = getDigit(n) ;
    if (len > 1)
        printf("The integer %lld has %d digits.\n",n, len) ;
    else
        printf("The integer %lld has %d digit.\n",n, 1) ;
    return 0 ;    
}