#include<stdio.h>
int flen(int);
int main() {
    int n,k,i,tmp,j;
    int que[10000];
    int ans[10000];
    while(scanf("%d%d",&n,&k)==2) {
        tmp=n;
        for(int ak=0;ak<10000;ak++) {
            que[ak]=0;
            ans[ak]=0;
        }
        ans[0]=n/k;
        n%=k;
        for(i=1;!que[n];i++) {
            que[n]=i;
            ans[i]=n*10/k;
            n=n*10%k;
        }
        j=que[n];
        // printf("j = %d\n",j);
        printf("%d/%d = ",tmp,k);
        printf("%d.",ans[0]);
        for(int count=1;count<j;count++) {
            printf("%d",ans[count]);
        }
        putchar('(');
        int len=0,flag=1;
        for(;j<i;j++) {
            len+=flen(ans[j]);
            if(len<=50) printf("%d",ans[j]);
            else if(len>50&&flag) {
                tmp=flen(ans[j]);
                len-=tmp;
                for(int count=tmp;len<50;count--) {
                    int ttmp=ans[j];
                    for(int tmr=count-1;tmr;tmr--) {
                        ttmp/=10;
                    }
                    printf("%d",ttmp);
                    len++;
                }
                len++;
                printf("...");
                flag=0;
            }
        }
        putchar(')');
        printf("\n   %d = number of digits in repeating cycle\n\n",len);
    }
    return 0;
}
int flen(int n) {
    int result=1;
    while(n>9) {
        result++;
        n/=10;
    }
    return result;
}