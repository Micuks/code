#include<stdio.h>
#include<string.h>
void process(char* a,char c,int tot,int len) {
    int count=0,flag=0;
    int left,right;
    for(int i=tot;i>=0;i--) {
        if(a[i]==c) {
            if(i<tot) count++;
            left=i;
        }
        else if(i<tot) break;
    }
    for(int i=tot-1;i<len;i++) {
        if(a[i]==c) {
            if(i>tot-1) count++;
            right=i;
            // printf("right = %d\n",right);
        }
        else if(i>tot-1) break;
    }
    // printf("left = %d, right = %d\n",left,right);
    if(count>=2) {
        if(count<len) {
            // printf("count = %d, len = %d\n",count,len);
            c=a[right+1];
            for(int i=right+2;i<=len;i++) {
                a[i-count-1]=a[i];
            }
            // printf("a = %s\n",a);
            if(a[left-1]==c) {
                process(a,c,left,len-count-1);
            }
            else flag=1;
        }
        else if(tot>0) for(int i=0;i<len;i++) a[i]='\0';
        else flag=1;
    }
    else flag=1;
    if(flag) {
        // printf("yes\n");
        for(int i=len;i>tot;i--) {
            a[i]=a[i-1];
        }
        a[tot]=c;
    }
}
void first(char* a,char* cptr,int* totptr,int* lenptr) {
    int count=0,left,right,tot=*totptr-1,len=*lenptr;
    char c=*cptr;
    for(int i=tot;i>=0;i--) {
        if(a[i]==c) {
            if(i<tot) count++;
            left=i;
        }
        else if(i<tot) break;
    }
    for(int i=tot-1;i<len;i++) {
        if(a[i]==c) {
            if(i>tot-1) count++;
            right=i;
            // printf("right = %d\n",right);
        }
        else if(i>tot-1) break;
    }
    // printf("left = %d, right = %d\n",left,right);
    if(count>=2) {
        if(count<len) {
            printf("count = %d, len = %d\n",count,len);
            *cptr=a[right+1];
            *totptr=left+1;
            *lenptr=len-count-1;
            printf("*lenptr = %d,len = %d\n",*lenptr,len);
            for(int i=right+2;i<=len;i++) {
                a[i-count-1]=a[i];
            }
            // printf("a = %s\n",a);
        }
        else for(int i=0;i<len;i++) a[i]='\0';
    }
}
int main() {
    int tot;
    char a[105];
    char c;
    scanf("%c%d%s",&c,&tot,a);
    int len=strlen(a);
    first(a,&c,&tot,&len);
    // printf("c = %c\n",c);
    process(a,c,tot-1,len);
    if(*a=='\0') printf("win\n");
    else printf("%s\n",a);
    return 0;
}
