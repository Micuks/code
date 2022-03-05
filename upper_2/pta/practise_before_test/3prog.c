#include<stdio.h>
int process(int number) {
    if(number/10==0) return number;
    int nxt=number%10+process(number/10);
    if(nxt<10) return nxt;
    else return nxt%10+nxt/10; 
}
int main() {
    int t,result=0;
    char temp;
    scanf("%d",&t);
    for(int i=0;i<t;i++) {
        result=0;
        if(i==0) getchar();
        while((temp=getchar())>='0'&&temp<='9') {
            result+=temp-'0';
        }
        if(result/10==0) printf("%d\n",result);
        else printf("%d\n",process(result));
    }
    return 0;
}