#include<stdio.h>
int fastpow_mod_11(int base,int power) {
    long long result=1;
    while(power) {
        if(power&1) result=result*base%11;
        power>>=1;
        base=1ll*base*base%11;
    }
    return result%11;
}
int main() {
    for(int i=0;i<17;i++) {
        printf("2^%d(mod 11) = %d\n",i+1,fastpow_mod_11(2,i+1));
    }
    return 0;
}