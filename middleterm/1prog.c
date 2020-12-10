#include<stdio.h>
void InsertSort(int a[], int n) {
    int temp,flag;
    for(int i=1;i<n;i++) {
        flag=1;
        for(int j=0;j<i&&flag;j++) {
            if(a[i]<a[j]) {
                flag=0;
                for(int k=i;k>j;k--) {
                    temp=a[k];
                    a[k]=a[k-1];
                    a[k-1]=temp;
                }
            }
        }
    }
    // for(int i=0;i<n;i++) printf(" %d"+!i,a[i]);
    // putchar('\n');
}
int main() {
    int m=0,n,sum=0,now=0;
    int a[1005];
    scanf("%d",&n);
    for(int i=0;i<n;i++) {
        scanf("%d",a+i);
        sum+=a[i];
    }
    InsertSort(a,n);
    while(now<<1<=sum) {//>half
        now+=a[--n];
        m++;
    }
    printf("%d\n",m);
    return 0;
}