#include<stdio.h>
int count1Binary(int n) {
    int count=0;
    for(;n;n>>=1) {
        count++;
    }
    return count;
}
int countBinary(int n) {
    if(!(n>>1)) return 1;
    return countBinary(n>>1)+1;
}
int main()
{
    int        n;

    scanf("%d",&n);
    printf("%d\n",countBinary(n));

    return 0 ;
}