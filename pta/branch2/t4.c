#include<stdio.h>
int GCD(int a,int b) {
    printf("a%%b = %d,b%%a = %d",a%b,b%a);
    if(a==1||b==1) return a==1?b:a;
    return a>b?GCD(b,a%b):GCD(a,b%a);
}
int main()
{
    int        a , b ;

    scanf("%d%d", &a , &b );
    printf("a = %d,b = %d\n",a,b);
    printf( "%d\n" , GCD( a, b ) ) ;

    return 0 ;    
}