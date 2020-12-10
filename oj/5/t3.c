#include<stdio.h>
int main() {
    int n, temp;
    int num[205];
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",num+i);
    for(int i=1;i<n-1;i++) {
        if(num[i]%2==0) 
            for(int j=i;j>0;j--) {
                if(num[j-1]&1) {
                    temp=num[j];
                    num[j]=num[j-1];
                    num[j-1]=temp;
                }
                else break;
            }
    }
    for(int i=0;i<n;i++) printf(" %d"+!i,num[i]);
    putchar('\n');
    return 0;
}