#include <stdio.h>

int findMax(int n) {
    int num;
    scanf("%d",&num);
    if(n==1) return num;
    int num1=findMax(n-1);
    return num>num1?num:num1;
}

int main()
{   
    int n ; 

    scanf("%d", &n); 
    printf("%d\n" , findMax( n ) ) ; 

    return 0;
}
