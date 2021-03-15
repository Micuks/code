#include <stdio.h>

//字符串转换函数，将source按规则转换后保存在target中
void getCounts(char source[], char target[]);

int main()
{
    char source[100000], target[100];

    scanf("%s", source);
    getCounts(source, target);
    printf("%s\n", target);

    return 0;
}
int getlen(int i) {
    int result=1;
    while((i/10)!=0) {
        result++;
        i/=10;
    }
    // printf("getlen = %d\n",result);
    return result;
}
int ksm(int base,int power) {
    long long result=1;
    while(power) {
        if(power&1) result=1ll*base*result;
        power>>=1;
        base*=base;
    }
    // printf("ksm = %lld\n",result);
    return result;
}
void getCounts(char source[], char target[]) {
    int ptr=-1;
    int count[15];
    for(int i=0;i<10;i++) count[i]=0;
    while(source[++ptr]!='\0') {
        count[source[ptr]-'0']++;
    }
    // for(int i=0;i<10;i++) {
    //     printf("count[%d] = %d\n",i,count[i]);
    // }
    ptr=-1;
    for(int i=0;i<10;i++) {
        if(count[i]) {
            int n=getlen(count[i]);
            int t=count[i];
            for(int j=0;j<n;j++) {
                target[++ptr]='0'+(t/ksm(10,n-1-j))%10;
                // printf("%c",target[ptr]);
            }
            target[++ptr]=i+'0';
        }
    }
    // printf("%s\n",target);
    target[++ptr]='\0';
}