#include<stdio.h>
#include<string.h>
#define MAXN 200
#define EPS 1e-5
const char* subject[]={"Chinese","Mathematics","English","Programming"};
struct STUDENT {
    char sid[15];
    char cid[15];
    char nam[15];
    int s[10];
    int passed;
};
struct STUDENT stu[MAXN];
int n=0,u=0;
int removed[MAXN];
void add() {
    for(;;) {
        int flag=1;
        printf("Please enter the SID, CID, name and four scores. Enter 0 to finish.\n");
        scanf("%s",stu[n].sid);
        if(strcmp(stu[n].sid,"0")==0) break;
        for(int i=0;i<n;i++) {
            if(strcmp(stu[i].sid,stu[n].sid)==0) {
                    flag=0;
                    if(removed[i]==1) flag=1;
                    if(flag==0) printf("Duplicated SID.\n");
            }
        }
        stu[n].passed=0;
        scanf("%s%s%d%d%d%d",stu[n].cid,stu[n].nam,&stu[n].s[0],&stu[n].s[1],&stu[n].s[2],&stu[n].s[3]);
        stu[n].s[4]=stu[n].s[0]+stu[n].s[1]+stu[n].s[2]+stu[n].s[3];
        for(int j=0;j<4;j++) {
            if(stu[n].s[j]>=60) stu[n].passed++;
        }
        if(flag) n++;
    }
}

void addstd() {
    for(;;) {
        printf("Please enter the SID, CID, name and four scores. Enter 0 to finish.\n");
        scanf("%s",stu[n].sid);
        if(strcmp(stu[n].sid,"0")==0) return;
        scanf("%d%s",&stu[n].cid,stu[n].nam);
        for(int i=0;i<4;i++)
            scanf("%d",&stu[n].s[i]),stu[n].s[4]+=stu[n].s[i];
        for(int i=0;i<n;i++)
            if(removed[i]==0&&(strcmp(stu[i].sid,stu[n].sid)==0)) {
                printf("Duplicated SID.\n");
                stu[n].s[4]=stu[n].cid=0;
                break;
            }
        if(removed[n]==0) n++;
    }
}
int rank(int score) {
    int result=0;
    int flag;
    for(int i=0;i<n;i++) {
        flag=1;
        if(removed[i]==1) flag=0;
        if(stu[i].s[4]>score&&flag) result++;
    }
    return result+1;
}
// void DQ(int isq) {
//     char s[MAXN];
//     for(;;) {
//         printf("Please enter SID or name.Enter 0 to finish.\n");
//         scanf("%s",s);
//         if(strcmp(s,"0")==0) break;
//         int r=0;
//         for(int i=0;i<n;i++) if(!removed[i]) {

//         }
//     }
// }
void rem(int type) {
    int cnt;
    for(;;) {
        cnt=0;
        // printf("type = %d\n",type);
        printf("Please enter SID or name. Enter 0 to finish.\n");
        scanf("%s",stu[n].sid);
        if(strcmp(stu[n].sid,"0")==0) break;
        else if(stu[n].sid[0]<='9'&&stu[n].sid[0]>='0') {
            for(int i=0;i<n;i++) {
                if(strcmp(stu[i].sid,stu[n].sid)==0) {
                    if(type==0) {
                        removed[i]=1;
                        cnt++;
                    }
                    else if(type==1) printf("%d %s %s %s %d %d %d %d %d %.2f\n",rank(stu[i].s[4]),stu[i].sid,stu[i].cid,stu[i].nam,stu[i].s[0],stu[i].s[1],stu[i].s[2],stu[i].s[3],stu[i].s[4],stu[i].s[4]/4.0+EPS);
                }
            }
            if(type==0) printf("%d student(s) removed.\n",cnt);
        }
        else {
            for(int i=0;i<n;i++) {
                if(strcmp(stu[i].nam,stu[n].sid)==0) {
                    if(type==0) {
                        removed[i]=1;
                        cnt++;
                    }
                    else if(type==1) {
                        printf("%d %s %s %s %d %d %d %d %d %.2f\n",rank(stu[i].s[4]),stu[i].sid,stu[i].cid,stu[i].nam,stu[i].s[0],stu[i].s[1],stu[i].s[2],stu[i].s[3],stu[i].s[4],stu[i].s[4]/4.0+EPS);
                    }
                }
            }
            if(type==0) {
                printf("%d student(s) removed.\n",cnt);
            }
        }
    }
}
void whole() {
    int ssum[MAXN],spas[MAXN],sfai[MAXN],p[MAXN];
    memset(ssum,0,sizeof(ssum));
    memset(spas,0,sizeof(spas));
    memset(sfai,0,sizeof(sfai));
    memset(p,0,sizeof(p));
    int flag;
    for(int i=0;i<n;i++) {
        flag=1;
        if(removed[i]==1) flag=0;
        if(flag) {
            for(int j=0;j<4;j++) {
                ssum[j]+=stu[i].s[j];
                if(stu[i].s[j]>=60) spas[j]++;
                else sfai[j]++;
            }
            p[stu[i].passed]++;
        }
    }
    for(int i=0;i<4;i++) {
        printf("%s\n"
            "Average Score: %.2f\n"
            "Number of passed students: %d\n"
            "Number of failed students: %d\n\n",
            subject[i],(double)ssum[i]/(double)(spas[i]+sfai[i])+EPS,spas[i],sfai[i]);
    }
    printf("Overall:\n"
        "Number of students who passed all subjects: %d\n"
        "Number of students who passed 3 or more subjects: %d\n"
        "Number of students who passed 2 or more subjects: %d\n"
        "Number of students who passed 1 or more subjects: %d\n"
        "Number of students who failed all subjects: %d\n\n",
        p[4], p[3]+p[4], p[2]+p[3]+p[4], p[1]+p[2]+p[3]+p[4], p[0]);
}
void part(char* cid) {
    int flag;
    int ssum[MAXN],spas[MAXN],sfai[MAXN],p[MAXN];
    memset(ssum,0,sizeof(ssum));
    memset(spas,0,sizeof(spas));
    memset(sfai,0,sizeof(sfai));
    memset(p,0,sizeof(p));
    for(int i=0;i<n;i++) {
        flag=1;
        for(int k=0;k<u;k++) {
            if(removed[k]==i) flag=0;
        }
        if(strcmp(stu[i].cid,cid)==0&&flag) {
            for(int j=0;j<4;j++) {
                ssum[j]+=stu[i].s[j];
                if(stu[i].s[j]>=60) spas[j]++;
                else sfai[j]++;
            }
            p[stu[i].passed]++;
        }
    }
    for(int i=0;i<4;i++) {
        printf("%s\n"
            "Average Score: %.2f\n"
            "Number of passed students: %d\n"
            "Number of failed students: %d\n\n",
            subject[i],(double)ssum[i]/(double)(spas[i]+sfai[i])+EPS,spas[i],sfai[i]);
    }
    printf("Overall:\n"
        "Number of students who passed all subjects: %d\n"
        "Number of students who passed 3 or more subjects: %d\n"
        "Number of students who passed 2 or more subjects: %d\n"
        "Number of students who passed 1 or more subjects: %d\n"
        "Number of students who failed all subjects: %d\n\n",
        p[4], p[3]+p[4], p[2]+p[3]+p[4], p[1]+p[2]+p[3]+p[4],p[0]);
}
void sta() {
    printf("Please enter class ID, 0 for the whole statistics.\n");
    scanf("%s",stu[n].sid);
    if(strcmp(stu[n].sid,"0")==0){
        whole();
    }
    else {
        part(stu[n].sid);
    }
}
void printmenu() {
    printf("Welcome to Student Performance Management System (SPMS).\n\n"
            "1 - Add\n"
            "2 - Remove\n"
            "3 - Query\n"
            "4 - Show ranking\n"
            "5 - Show Statistics\n"
            "0 - Exit\n\n");
}
void debug() {
    for(int i=0;i<n;i++) {
        printf("%s %s %s %d %d %d %d %d %d %d\n",stu[i].sid,stu[i].cid,stu[i].nam,stu[i].s[0],stu[i].s[1],stu[i].s[2],stu[i].s[3],stu[i].s[4],stu[i].passed,removed[i]);
    }
}
int main() {
    for(int i=0;i<MAXN;i++) {
        stu[i].passed=0;
    }
    for(;;) {
        printmenu();
        // debug();
        int choice;
        scanf("%d",&choice);
        if(choice==1) add();
        else if(choice==2) rem(0);
        else if(choice==3) rem(1);
        else if(choice==4) printf("Showing the ranklist hurts students' self-esteem. Don't do that.\n");
        else if(choice==5) sta();
        else if(choice==-1) debug();
        else break;
    }
    return 0;
}