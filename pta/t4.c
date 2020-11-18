#include<stdio.h>
int power(int base,int pow) {
    long long result=1;
    while(pow) {
        if(pow&1) result*=base;
        pow>>=1;
        base=1ll*base*base;
    }
    return result;
}
int reverseNum(int n) {
    int t=n,len=1;
    while(t/=10) len++;
    //printf("len = %d    ",len);
    if(n<10) return n;
    else return reverseNum(n/10)+n%10*power(10,(len-1));
}
int main()
{
    int        num ;

    scanf("%d",&num);
    printf("The reverse form of number %d is %d.\n",num,reverseNum(num)) ;

    return 0;
}