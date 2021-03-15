#include<stdio.h>
#include<string.h>
void process(char *a,int n,int tot);
int main() {
    char a[105];
    char c;
    int n;
    scanf("%c%d%s",&c,&n,a);
    n--;
    int len=strlen(a);
    for(int i=len;i>n;i--) a[i]=a[i-1];
    a[n]=c;
    len++;
    process(a,len,n);
    if(*a=='\0') printf("win\n");
    else printf("%s\n",a);
    return 0;
}
void process(char* a,int len,int tot) {
    int count=0;
    int left=tot,right;
    for(int i=tot;i<len;i++) {
        if(a[i]==a[tot]) {
            count++;
            right=i;
        }
        else break;
    }
    for(int i=tot-1;i>-1;i--) {
        if(a[i]==a[tot]) {
            count++;
            left=i;
        }
        else break;
    }
    if(count>=3) {
        for(int i=left;i<=len-count;i++) {
            a[i]=a[i+count];
        }
        // printf("%s\n",a);
        tot=left;
        len-=count;
        if(a[tot-1]==a[tot]) {
            process(a,len,tot);
        }
    }
}