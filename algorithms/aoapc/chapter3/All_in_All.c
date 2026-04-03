#include<stdio.h>
#define MAXN 1048576    
int main() {
    int i=0,j=0;
    char s[MAXN],t[MAXN];
    while(scanf("%s%s",s,t)==2) {
        char *ps=s,*pt=t;
        for(;*pt!='\0'&&*ps!='\0';pt++) {
            if(*pt==*ps) ps++;
        }
        if(*ps=='\0') printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}