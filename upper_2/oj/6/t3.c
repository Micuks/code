#include<stdio.h>
int rowmax(int (*a)[105],int i,int m) {
    int result=0;
    // for(int k=0;k<4;k++){
    //     for(int l=0;l<5;l++)
    //         printf(" %d"+!l,a[k][l]);
    //     putchar('\n');
    // }
    for(int j=1;j<m;j++) {
        if(a[i][j]>a[i][result]) {
            result=j;
        }
    }
    return result;
}
int columnmin(int (*a)[105],int j,int n) {
    int result=0;
    // for(int k=0;k<n;k++){
    //     for(int l=0;l<5;l++)
    //         printf(" %d"+!l,a[k][l]);
    //     putchar('\n');
    // }
    for(int i=1;i<n;i++) {
        if(a[i][j]<a[result][j]) {
            result=i;
        }
    }
    return result;
}
int main() {
    int m,n;
    int flag=1;
    scanf("%d%d",&n,&m);
    int matrix[105][105];
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            scanf("%d",&matrix[i][j]);
            // printf(" %d"+!j,matrix[i][j]);
        }
        // putchar('\n');
    }
    for(int i=0;i<n&&flag;i++) {
        int col=rowmax(matrix,i,m);
        int row=columnmin(matrix,col,n);
                // printf("i = %d,col = %d,row = %d\n",i,col,row);
        if(i==row) {
            printf("The saddle point is (%d,%d)=%d.\n",row,col,matrix[row][col]);
            flag=0;
        }
    }
    if(flag) printf("There is no saddle point in the matrix.\n");
    return 0;
}