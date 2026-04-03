#include<stdio.h>
#include<stdlib.h>
int main() {
    int n,m;
    scanf("%d%d",&n,&m);
    int **matrix=(int**) malloc(sizeof(int*)*n);
    for(int i=0;i<n;i++) matrix[i]=(int*)malloc(sizeof(int)*m);
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            scanf("%d",&matrix[i][j]);
        }
    }
    int **ans=(int**)malloc(sizeof(int*)*m);
    for(int i=0;i<m;i++) ans[i]=(int*)malloc(sizeof(int)*n);
    for(int i=0;i<m;i++) {
        for(int j=0;j<n;j++) {
            ans[i][j]=matrix[j][i];
            printf(" %d"+!j,ans[i][j]);
        }
        putchar('\n');
    }
    return 0;
}