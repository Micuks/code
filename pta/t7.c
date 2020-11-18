#include<stdio.h>
int sq1rt(int num) {
    for(int i=1;;i++) {
        if(i*i>num) return i-1;
    }
}
int isPerfect(int num) {
    if(num==1) return 0;
    int ans=1;
    int sq=sq1rt(num);
    // printf("sq = %d\t",sq);
    for(int i=2;i<=sq;i++) {
        if(num%i==0) ans+=(i+num/i);
    }
    // printf("ans = %d\t",ans);
    if(num==ans) return 1;
    return 0;
}
void printPerfact(int num) {
    int sq=sq1rt(num);
    int ptr=0;
    int leftnumbers[500];
    printf("%d=1",num);
    for(int i=2;i<sq;i++) {
        if(num%i==0) {
            printf("+%d",i);
            leftnumbers[ptr]=num/i;
            ptr++;
        }
    }
    if(num==sq*sq) printf("+%d",sq);
        else if(num%sq==0) {
            printf("+%d",sq);
            leftnumbers[ptr]=num/sq;
            ptr++;
        }
    while(ptr--) printf("+%d",leftnumbers[ptr]);
    putchar('\n');
}

int main()
{
    int i,a,b,count;

    scanf("%d%d",&a,&b);
    count = 0 ;
    for(i=a;i<=b;i++)
    {
        if (isPerfect(i))  
        {
            printPerfact(i) ;
            count ++ ;  
        }        
    }
    printf("The total number is %d.\n",count);
    return 0 ;
}