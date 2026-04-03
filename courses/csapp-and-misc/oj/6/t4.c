#include<stdio.h>
void transrow(int (*a)[105],int n,int row1,int row2) {
    int temp;
    for(int j=0;j<n;j++) {
        temp=a[row1][j];
        a[row1][j]=a[row2][j];
        a[row2][j]=temp;
    }
}
int sum(int*a,int n) {
    int result=0;
    for(int i=0;i<n;i++) result+=a[i];
    return result;
}
void sort(int (*a)[105],int n) {
    for(int i=0;i<n-1;i++) {
        for(int j=n-1;j>i;j--) {
            int sum1=sum(*(a+j),n);
            int sum2=sum(*(a+j-1),n);
                    // printf("sum1 = %d, sum2 = %d\n",sum1,sum2);
            if(sum1<sum2) transrow(a,n,j,j-1);
        }
    }
}
int main() {
    int n,a[105][105];
    scanf("%d",&n);
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            scanf("%d",(*(a+i)+j));
            // printf(" %d"+!j,*(*(a+i)+j));
        }
        // putchar('\n');
    }
    // int num=1000000*100;
    // printf("%d\n",num);
    sort(a,n);
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            printf(" %d"+!j,a[i][j]);
        }
        putchar('\n');
    }
    return 0;
}