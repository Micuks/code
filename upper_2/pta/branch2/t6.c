#include<stdio.h>
int sqrt(int n) {
    for(int i=0;;i++) {
        if(i*i<=n&&(i+1)*(i+1)>n) return i;
    }
}
int isPrime(int n) {
    if(n==1) return 0;
    if(n==2||n==3) return 1;
    if((n%2==0)||(n%3==0)) return 0;
    if(n%6!=1&&n%6!=5) return 0;
    int sq=sqrt(n);
    for(int i=5;i<=sq;i+=6) if((n%i==0)||(n%(i+2)==0)) return 0;
    return 1;
}
void printFactor(int n,int i) {
    if(i==1) {
        printf("%d=",n);
        i=0;
    }
    int oi=i;
    if(n==1&&i==0) {
        printf("1\n");
        return;
    }
    for(int j=2;j<=n;j++) {
        if(isPrime(j)) {
            if(n%j==0) {
                printf("*%d"+!i,j);
                if(!i) i=j;
                if(i>0&&oi==i) i=-1;
                printFactor(n/j,i);
                if(j==i) putchar('\n');
                break;
            }
        }
    }
}
int main()
{
    int a,b,i ;

    scanf( "%d%d", &a, &b );
    for( i = a ; i <= b ; i++ )
        printFactor( i , 1 ) ;    

    return 0;
}