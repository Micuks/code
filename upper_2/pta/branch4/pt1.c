#include<stdio.h>
#include<malloc.h>
int main() {
    int n;
    scanf("%d",&n);
    int* a=(int*)malloc(n*sizeof(int));
    for(int i=0;i<n;i++) {
        scanf("%d",&a[i]);
        a[i]=-10*a[i];
        printf(" %d"+!i,a[i]);
    }
        free(a);
    return 0;
}
