#include<stdio.h>
int con1vert(int n) {
    int base=1,result=0;
    for(;n;base<<=1) {
        if(n&1) result+=base;
        n/=10;
    }
    // printf("result = %d\t",result);
    return result;
}
int convert(int n) {
    if(!(n/10)) return n;
    return convert(n/10)<<1+n%10;
}
/* int convert(int n) {
    if(n/10) return n;
    
} */
int main()
{
    int        n ;

    scanf("%d",&n);

    printf("%d\n",convert(n)) ;
    return 0 ;    
}