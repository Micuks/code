#include<stdio.h>
void strCopy(int *a1,int *a2) {
    for(;*a1=*a2;a1++,a2++)
        ;
}
int main() {
    int n, temp;
    int num[205];
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",num+i);
    for(int i=0;i<n-1;i++) {
        // printf("num[%d] = %d\n",i,num[i]);
        for(int j=i;j>=0&&(num[j]&1&&(num[j+1]%2==0));j--) {
            temp=num[j];
            num[j]=num[j+1];
            num[j+1]=temp;
        }
        // for(int j=0;j<n;j++) printf(" %d"+!j,num[j]);
        // putchar('\n');
    }
    for(int i=0;i<n;i++) printf(" %d"+!i,num[i]);
    putchar('\n');
    return 0;
}