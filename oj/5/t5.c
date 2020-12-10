#include<stdio.h>
int main() {
    int n,count;
    int note[] = {100,50,20,10,5,2,1};
    scanf("%d",&n);
    for(int i=0;i<7&&n;i++) {
        count=0;
        while(n/note[i]) {
            count+=(n/note[i]);
            n-=note[i]*count;
        }
        if(count) printf("%d:%d\n",note[i],count);
    }
    return 0;
}