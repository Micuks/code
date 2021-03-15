#include<stdio.h>
#include<malloc.h>
int main() {
    int n,m;
    scanf("%d%d",&n,&m);
    int **a=(int**)malloc(n*sizeof(int*));
    for(int i=0;i<n;i++) {
        a[i]=(int*)malloc(m*sizeof(int));
    }
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            scanf("%d",*(a+i)+j);
        }
    }
    // for(int i=0;i<n;i++) {
    //         for(int j=0;j<m;j++)
    //             printf(" %d"+!j,a[i][j]);
    //         printf("\n");
    //     }
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            a[i][j]=-10*a[i][j];
        }
    }
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++)
            printf(" %d"+!j,a[i][j]);
        printf("\n");
    }
    for(int i=0;i<n;i++) free(a[i]);
    free(a);
    return 0;
}