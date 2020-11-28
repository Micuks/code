#include<stdio.h>
#include<string.h>
const char sign[]="~!@#$%^&*()[]}{|<>?/.,:\"\';";
int main() {
    int n,len,count;
    int ans[5];
    char input[35];
    scanf("%d",&n);
    while(n--) {
        count=0;
        for(int i=0;i<5;i++) ans[i]=0;
        scanf("%s",input);
        len=strlen(input);
        for(int i=0;i<len;i++) {
            if((input[i]-'0')>=0&&(input[i]-'0')<=9&&!ans[0]) {
                // printf("input[%d] = %c, ans[0] = %d\n",i,input[i],ans[0]);
                ans[0]=1;
                break;
            }
        }
        for(int i=0;i<len;i++) {
            if((input[i]-'A')>-1&&(input[i]-'Z')<1&&!ans[1]) {
                // printf("input[%d] = %c, ans[1] = %d\n",i,input[i],ans[1]);
                ans[1]=1;
                break;
            }
        }
        for(int i=0;i<len;i++) {
            if((input[i]-'a')>-1&&(input[i]-'z')<1&&!ans[2]) {
                // printf("input[%d] = %c, ans[2] = %d\n",i,input[i],ans[2]);
                ans[2]=1;
                break;
            }
        }
        for(int i=0;i<len;i++) {
            int len_of_sign=strlen(sign);
            for(int j=0;j<len_of_sign;j++) {
                if(input[i]==sign[j]&&!ans[3]) {
                    // printf("input[%d] = %c, sign[%d] = %c,ans[3] = %d\n",i,input[i],j,sign[j],ans[3]);
                    ans[3]=1;
                    break;
                }
            }
        }
        for(int i=0;i<4;i++) {
            if(ans[i]) count++;
        }
        if(count>=3&&len>5) printf("yes\n");
        else printf("no\n");
    }
    return 0;
}