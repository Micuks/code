#include <stdio.h>

void bubbleSort(int a[], int n) {
    for(int m=n-1;m>0;m--) {
        for(int i=0;i<m;i++) {
            if(a[i]>a[i+1]) {
                a[i]+=a[i+1];
                a[i+1]=a[i]-a[i+1];
                a[i]-=a[i+1];
            }
        }
    }
}

void outputData(int data[], int elementCount) {
    for(int i=0;i<elementCount;i++) {
        printf(" %d"+!i,data[i]);
    }
    putchar('\n');
}

int main()
{
    int n, i, num[10010];

    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &num[i]);
    bubbleSort(num, n);
    outputData(num, n);
    return 0;
}