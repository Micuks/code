#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int cmp(const void* a,const void* b) {
    return *(int*)a-*(int*)b;
}
int main() {
    int an,bn,flag=1;
    char as[105],bs[105];
    while (scanf("%s%s",as,bs)==2) {
        int ac[30]={0},bc[30]={0};
        an=strlen(as);
        bn=strlen(bs);
        flag=1;
        if(an==bn) {
            for(int i=0;i<an;i++) {
                ac[as[i]-'A']++;
                bc[bs[i]-'A']++;
            }
            qsort(ac,26,sizeof(int),cmp);
            qsort(bc,26,sizeof(int),cmp);
            for(int i=0;i<26;i++) if(ac[i]!=bc[i]) flag=0;
        }
        else flag=0;
        if(flag) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}