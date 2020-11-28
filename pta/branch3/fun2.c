#include <stdio.h>

int findMin(int data[], int startLoc, int endLoc) {
    int result=startLoc;
    for(int i=startLoc;i<=endLoc;i++) {
        if(data[result]>data[i]) result=i;
    }
    return result;
}
void outputData(int data[], int elementCount) {
    for(int i=0;i<elementCount;i++) 
        printf(" %d"+!i,data[i]);
    putchar('\n');
}
void selectSort(int data[], int elementCount) {
    int temp,min;
    for(int n=elementCount;n>1;n--) {
        temp=findMin(data,elementCount-n,elementCount-1);
        // data[elementCount-n]+=data[temp];
        // data[temp]=data[elementCount-n]-data[temp];
        // data[elementCount-n]-=data[temp];
        min=data[temp];
        data[temp]=data[elementCount-n];
        data[elementCount-n]=min;
        outputData(data,elementCount);
    }
}
int main()
{
    int n, i, num[1010];

    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &num[i]);
    selectSort(num, n);
    return 0;
}
