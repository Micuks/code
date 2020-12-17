#include<stdio.h>
int main() {
    int n,a[105][105];
    scanf("%d",&n);
    int tot=1,flag=0;//flag==0 向左下方填数；flag==1 向右上方填数；
    int xptr=0,yptr=0;
    while(tot<=n*n) {
        if(flag==1) a[xptr--][yptr++]=tot++;
        else a[xptr++][yptr--]=tot++;
        if(xptr==n) {
            xptr--;
            yptr+=2;
            flag=1;
        }
        if(yptr==n) {
            yptr--;
            xptr+=2;
            flag=0;
        }
        if(yptr==-1) {
            yptr++;
            flag=1;
        }
        if(xptr==-1) {
            xptr++;
            flag=0;
        }
        // printf("tot = %d\n",tot);
    }
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            printf(" %d"+!j,a[i][j]);
        }
        putchar('\n');
    }
    return 0;
}