#include<stdio.h>
#define maxn 25
int a[maxn]={0};
int pick(int n,int p,int k,int t){
    while(k--) {
        do{p=(p+t+n-1)%n+1;} while(a[p]==0);
    }
    return p;
}
int main() {
    int n,k,m,p,q;
    while(scanf("%d%d%d",&n,&k,&m)==3&&n) {
        a[maxn]={0};
        p=0,q=n+1;
        int left=n;
        for(int i=1;i<=n;i++) a[i]=1;
        while(left) {
            p=pick(n,p,k,1);
            q=pick(n,q,m,-1);
            printf("%3d",p);
            left--;
            if(p!=q) {
                printf("%3d",q);
                left--;
            }
            a[p]=a[q]=0;
            if(left) putchar(',');
        }
        putchar('\n');
    }
    return 0;
}