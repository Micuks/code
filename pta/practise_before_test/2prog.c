#include<stdio.h>
int solveKS(int books[],int index,int capacity) {
    if(index<0||capacity<=0) return 0;
    int result=solveKS(books,index-1,capacity);
    if(books[index]<=capacity) {
        if(1+solveKS(books,index-1,capacity-books[index])>result) result=1+solveKS(books,index-1,capacity-books[index]); 
    }
    return result;
}
int main() {
    int n;
    int books[105],isuntoken[105];
    scanf("%d",&n);
    for(int i=0;i<n;i++) {
        isuntoken[i]=1;
        scanf("%d",books+);
    }
    printf("%d\n",solveKS(books,n,1000));
}   