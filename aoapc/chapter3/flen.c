#include<stdio.h>
int flen(long long);
int main() {
    long long asdf;
    while( scanf("%lld",&asdf)==1)
    printf("the length of %lld is %d\n",asdf,flen(asdf));
    return 0;
}
int flen(long long n) {
    int result=1;
    while(n>9) {
        result++;
        n/=10;
    }
    return result;
}