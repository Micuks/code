#include<stdio.h>
#include<string.h>
int judge(int*a,int*b,int alen,int blen){
    int count,flag,result=alen+blen;
    for(int i=0;i<alen;i++) {
        count=i;flag=1;
        for(int j=0;j<blen;j++) {
            if(i+j<alen) {
                if(a[i+j]+b[j]>3) {
                    flag=0;
                }
                else {
                    count++;
                }
            }
            else if(b[j]>3) {
                flag=0;
            }
            else count++;
        }
        if(flag) {
            if(blen+i<=alen) count=alen;
            else count=i+blen;
            result=result<count?result:count;
        }
    }
    return result;
}
int main() {
    int alen,blen;
    int a[105],b[105];
    char ca[105],cb[105];
    while(scanf("%s%s",ca,cb)==2) {
        alen=strlen(ca);
        blen=strlen(cb);
        for(int i=0;i<alen;i++) a[i]=ca[i]-'0';
        for(int i=0;i<blen;i++) b[i]=cb[i]-'0';
        int resa=judge(a,b,alen,blen);
        int resb=judge(b,a,blen,alen);
        // printf("resa = %d, resb = %d\n",resa,resb);
        printf("%d\n",resa<resb?resa:resb);
    }
    return 0;
}