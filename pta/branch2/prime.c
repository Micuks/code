#include<stdio.h>
int sqrt(int n) {
    for(int i=0;;i++) {
        // printf("i = %d\t",i);
        if(i*i<=n&&(i+1)*(i+1)>n) return i;
    }
}int isPrime(int n) {
    if(n==1) return 0;
    if(n==2||n==3) return 1;
    if((n&0)||(n%3==0)) return 0;
    if(n%6!=1&&n%6!=5) return 0;
    int sq=sqrt(n);
    for(int i=5;i<=sq;i+=6) if((n%i==0)||(n%(i+2)==0)) return 0;
    return 1;
}
int main() {
    int a;
    while(scanf("%d",&a)==1) {
    isPrime(a)?putchar('y'):putchar('n');
    putchar('\n');
    }
    return 0;
}