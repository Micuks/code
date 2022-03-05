#include<stdio.h>
#include<stdlib.h>
int main() {
    int n,temp;
    scanf("%d",&n);
    int *a;
    a=(int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++) scanf("%d",a+i);
    for(int i=0;i<n;i++) {
        int b;
        scanf("%d",&b);
        temp=a[i];
        a[i]=a[b];
        a[b]=temp;
    }
    for(int i=0;i<n;i++) printf(" %d"+!i,a[i]);
    putchar('\n');
    return 0;
}