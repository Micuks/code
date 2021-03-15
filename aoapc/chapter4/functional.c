#include<stdio.h>
int f(int n) {
    return n==0?1:f(n-1)*n;
}
int main() {
    int n;
    // scanf("%d",&n);
    n=100000000;
    printf("%d\n",f(n));
    return 0;
}