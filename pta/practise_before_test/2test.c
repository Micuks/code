#include<stdio.h>
long long fastpow(int base,int power) {
    long long result=1;
    while(power) {
        if(power&1) result*=base;
        power>>=1;
        base=1ll*base*base;
    }
    return result;
}
int main() {
    int n;
    scanf("%d",&n);
    printf("2^%d = %d\n",n,fastpow(2,n));
    return 0;
}