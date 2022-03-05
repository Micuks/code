#include<stdio.h>
int GCD(int a,int b) {
    if(a==0||b==0) return a+b;
    // printf("a%%b = %d,b%%a = %d",a%b,b%a);
    return a>b?GCD(b,a%b):GCD(a,b%a);
}
int main()
{
    int        a , b ;

    scanf("%d%d", &a , &b );
    printf( "%d\n" , GCD(a,b) ) ;

    return 0 ;    
}