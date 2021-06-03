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
        int flag=1;
        printf("Please enter the SID, CID, name and four scores. Enter 0 to finish.\n");
        scanf("%s",stu[n].sid);
        if(strcmp(stu[n].sid,"0")==0) return;
        scanf("%s%s",stu[n].cid,stu[n].nam);
        for(int i=0;i<4;i++)
            {
                scanf("%d",&stu[n].s[i]),stu[n].s[4]+=stu[n].s[i];
                if(stu[n].s[i]>=60) stu[n].passed++;
            }
        for(int i=0;i<n;i++)
            if(removed[i]==0&&(strcmp(stu[i].sid,stu[n].sid)==0)) {
                printf("Duplicated SID.\n");
                stu[n].s[4]=flag=stu[n].passed=0;
                break;
            }
        if(flag==1) n++;
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
int rankstd(int x) {
    int sum=0;
    for(int i=0;i<n;i++) 
        if(removed[i]==0&&stu[i].s[4]>stu[x].s[4]) sum++;
    return sum+1;
}
void rq(int cmd) {
    char id[15];
    for(;;) {
        printf("Please enter SID or name. Enter 0 to finish.\n");
        scanf("%s",id);
        if(strcmp(id,"0")==0) return;
        int cnt=0;
        for(int i=0;i<n;i++) {
            if(!removed[i]&&(strcmp(id,stu[i].sid)==0||strcmp(id,stu[i].nam)==0)) {
                if(cmd==0) removed[i]=1,cnt++;
                else {
                    printf("%d %s %s %s",rankstd(i),stu[i].sid,stu[i].cid,stu[i].nam);
                    for(int j=0;j<4;j++) printf(" %d",stu[i].s[j]);
                    printf(" %d %.2lf\n",stu[i].s[4],stu[i].s[4]/4.0+EPS);
                }
                if(id>="0"&&id<="9") break;
            }
        }
        if(cmd==0) printf("%d student(s) removed.\n",cnt);
    }
}
void rem(int type) {
    int cnt;
    char stringid[15]={};
    for(;;) {
        cnt=0;
        // printf("type = %d\n",type);
        printf("Please enter SID or name. Enter 0 to finish.\n");
        scanf("%s",stringid);
        if(!strcmp(stringid,"0")) return;
        for(int i=0;i<n;i++) {
            if(!removed[i]&&(!strcmp(stu[i].sid,stringid)||!strcmp(stu[i].nam,stringid))) {
                if(!type) {
                    cnt++;
                    removed[i]=1;
                }
                else {
                    printf("%d %s %s %s",rankstd(i),stu[i].sid,stu[i].cid,stu[i].nam);
                    for(int j=0;j<4;j++) printf(" %d",stu[i].s[j]);
                    printf(" %d %.2lf\n",stu[i].s[4],stu[i].s[4]/4.0+EPS);
                }
                if(*stringid>='0'&&*stringid<='9') break;
            }
        }
        if(!type) printf("%d student(s) removed.\n",cnt);
    }
}
char* itoa(int num,char* str,int radix)
{
    char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned unum;
    int i=0,j,k;

    if(radix==10&&num<0)
    {
        unum=(unsigned)-num;
        str[i++]='-';
    }
    else unum=(unsigned)num;
 
    do
    {
        str[i++]=index[unum%(unsigned)radix];
        unum/=radix;
    }while(unum);
 
    str[i]='\0';
 
    if(str[0]=='-') k=1;
    else k=0;
 
    char temp;
    for(j=k;j<=(i-1)/2;j++)
    {
        temp=str[j];
        str[j]=str[i-1+k-j];
        str[i-1+k-j]=temp;
    }
 
    return str;
 
}
void show_statistics() {
    printf("Please enter class ID, 0 for the whole statistics.\n");
    int pass[5]={},sum[5]={},num=0;
    int total[5]={};
    int id;
    scanf("%d",&id);
    char stringid[15]={};
    itoa(id,stringid,10);
    for(int i=0;i<n;i++) {
        if(removed[i]==0&&(!id||strcmp(stu[i].cid,stringid)==0)) {
            num++;
            int cnt=0;
            for(int j=0;j<4;j++) {
                total[j]+=stu[i].s[j];
                if(stu[i].s[j]>=60) pass[j]++,sum[++cnt]++;
            }
        }
    }
    for(int i=0;i<4;i++) {
        printf("%s\n"
		"Average Score: %.2lf\n"
		"Number of passed students: %d\n"
		"Number of failed students: %d\n\n",
        subject[i],(double)total[i]/(double)num+EPS,pass[i],num-pass[i]);
    }
    printf("Overall:\n"
	"Number of students who passed all subjects: %d\n",sum[4]);
	for(int i=3;i;i--)
		printf("Number of students who passed %d or more subjects: %d\n",i,sum[i]);
	printf("Number of students who failed all subjects: %d\n\n",num-sum[1]);//一科都没有通过的人,利用容斥原理 

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
        if(strcmp(stu[i].cid,cid)==0&&!removed[i]) {
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
    int id;
    char stringid[5]={};
    scanf("%d",&id);
    itoa(id,stringid,10);
    if(id==0){
        whole();
    }
    else {
        part(stringid);
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