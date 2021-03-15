#include<stdio.h>
int main() {
    int credit=-160;
    int n;
    scanf("%d",&n);
    while(n--) {
        int res,cas;
        scanf("%d%d",&res,&cas);
        if(cas>0) {
            if(res==1) credit+=5;
            else if(res==-1) credit-=15;
        }
        if(cas==0) {
            if(res==1) credit+=10;
            else if(res==-1) credit-=10;
        }
        if(cas<0) {
            if(res==1) credit+=15;
            else if(res==-1) credit-=5;
        }
    }
    printf("%d\n",credit);
    return 0;
}