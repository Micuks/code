#include <stdio.h>

//插入排序（升序）
//参数说明：数组，数组中已有元素个数
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
        for(int l=0;l<n;l++) printf(" %d"+!l,a[l]);
                    // printf(" %d",i);
        putchar('\n');
    }
}

int main()
{
    int n, i, num[1000];

    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &num[i]);
    InsertSort(num, n);
    return 0;
}
