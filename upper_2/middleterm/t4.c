#include <stdio.h>

#define MAXN 2000000
#define MAXM 100000

int RecurBinarySearch(int a[], int key, int left, int right) {
    if(left>right) return -1;
    int mid=(left+right)>>1;
    if(a[mid]==key) return mid;
    else if(a[mid]>key) RecurBinarySearch(a,key,left,mid-1);
    else if(a[mid]<key) RecurBinarySearch(a,key,mid+1,right);
}

int a[MAXN], loc[MAXM]; //由于n比较大，所以使用全局变量存储这n个整数；

int main()
{
    int n, m, i;
    scanf("%d %d", &n, &m);

    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for (i = 0; i < m; i++)
    {
        scanf("%d", &loc[i]);
        loc[i] = RecurBinarySearch(a, loc[i], 0, n - 1);
    }

    for (i = 0; i < m - 1; i++)
        printf("%d ", loc[i]);
    printf("%d\n", loc[m - 1]);
    return 0;
}