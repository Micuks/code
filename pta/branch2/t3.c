#include<stdio.h>
int countBinary(int n) {
    int count=0;
    for(;n;n>>=1) {
        count++;
    }
    return count;
}
int main()
{
    int        n;

    scanf("%d",&n);
    printf("%d\n",countBinary(n));

    return 0 ;
}