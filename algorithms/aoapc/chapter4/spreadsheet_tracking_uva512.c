#include<stdio.h>
#define MAXD 10000
int r,c,n;
struct COMMAND{
    char ord[4];
    int r1,r2,c1,c2;
    int num;
    int vec[16];
}cmd[MAXD];
int track(int*pr,int*pc) {
    for(int i=0;i<n;i++) {
        int dr=0,dc=0;
        if(cmd[i].ord[0]=='E') {
            if(cmd[i].r1==*pr&&cmd[i].c1==*pc) {
                *pr=cmd[i].r2;
                *pc=cmd[i].c2;
            }
            else if(cmd[i].r2==*pr&&cmd[i].c2==*pc) {
                *pr=cmd[i].r1;
                *pc=cmd[i].c1;
            }
        }
        if(cmd[i].ord[0]=='I') {
            if(cmd[i].ord[1]=='R') {
                for(int j=0;j<cmd[i].num;j++) {
                    if(cmd[i].vec[j]<=*pr) dr++;
                }
            }
            else if(cmd[i].ord[1]=='C') {
                for(int j=0;j<cmd[i].num;j++) {
                    if(cmd[i].vec[j]<=*pc) dc++;
                }
            }
            *pr+=dr;
            *pc+=dc;
        }
        else if(cmd[i].ord[0]=='D'){
            if(cmd[i].ord[1]=='R') {
                for(int j=0;j<cmd[i].num;j++) {
                    if(cmd[i].vec[j]==*pr) return 0;
                    else if(cmd[i].vec[j]<*pr) dr--;
                }
            }
            else if(cmd[i].ord[1]=='C') {
                for(int j=0;j<cmd[i].num;j++) {
                    if(cmd[i].vec[j]==*pc) return 0;
                    else if(cmd[i].vec[j]<*pc) dc--;
                }
            }
            *pr+=dr;
            *pc+=dc;
        }
    }
    return 1;
}
void printcmd() {
    for(int i=0;i<n;i++) {
        printf("cmd[%d].ord = %s    ",i,cmd[i].ord);
        printf("(%d,%d) (%d,%d) %d\n",
                cmd[i].r1,cmd[i].c1,cmd[i].r2,cmd[i].c2,cmd[i].num);
    }
}
int main() {
    int kase=0,pr,pc,m;
    while(scanf("%d%d%d",&r,&c,&n)==3&&r){
        for(int i=0;i<n;i++) {
            scanf("%s",cmd[i].ord);
            if(cmd[i].ord[0]=='E') scanf("%d%d%d%d",&cmd[i].r1,&cmd[i].c1,&cmd[i].r2,&cmd[i].c2);
            else {
                scanf("%d",&cmd[i].num);
                for(int j=0;j<cmd[i].num;j++) scanf("%d",&cmd[i].vec[j]);
            }
        }
        if(kase) putchar('\n');
        // printf("debug\n");
        // printcmd();
        printf("Spreadsheet #%d\n",++kase);
        scanf("%d",&m);
        while(m--) {
            scanf("%d%d",&pr,&pc);
            printf("Cell data in (%d,%d) ",pr,pc);
            if(track(&pr,&pc)) printf("moved to (%d,%d)\n",pr,pc);
            else printf("GONE\n");
        }
    }
    return 0;
}