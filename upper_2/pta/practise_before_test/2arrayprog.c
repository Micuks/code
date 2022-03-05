#include<stdio.h>
int dp(int books[],int n,int capacity) {
    int d[105][1010];
    for(int i=0;i<=capacity;i++) d[n][i]=0;
    for(int i=n-1;i>=0;i--) {
        for(int j=0;j<=capacity;j++) {
            if(i==n-1) d[i][j]=0;
            else d[i][j]=d[i+1][j];
            if(books[i]<=j) {
                if(d[i+1][j]<d[i+1][j-books[i]]+1) d[i][j]=d[i+1][j-books[i]]+1;
            }
        }
    }
    return d[0][capacity];
}
int main() {
    int n,books[105];
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",books+i);
    printf("%d\n",dp(books,n,1000));
}