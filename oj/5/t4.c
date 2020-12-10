#include<stdio.h>
int main() {
    int n,ans=1,count=1,a[1005];
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",a+i);
    // for(int i=0;i<n;i++) printf(" %d"+!i,a[i]);
    for(int i=0;i<n-1;i++) {
        if(a[i]==a[i+1]) {
            count++;
            (count>ans)?(ans=count):(ans=ans);
        }
        else count=1;
    }
    printf("%d\n",ans);
    return 0;
}