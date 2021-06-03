#include<stdio.h>
int main() {
    int a[100];
    a[0]=0+0+0+1;
    a[1]=1+0+0+1;
    a[2]=1+1+0+1;
    a[3]=1+0+1+0;
    for(int i=0;i<4;i++) {
        if(a[i]==3) printf("The eater is %d\n",i+1);
    }
    return 0;
}