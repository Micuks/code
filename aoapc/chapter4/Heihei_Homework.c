#include<stdio.h>
#include<string.h>
#define MAXN 200
#define EPS 1e-5
const char* subject[]={"Chinese","Mathematics","English","Programming","ALL"};
struct STUDENT {
    char sid[MAXN];
    char cid[MAXN];
    char nam[MAXN];
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

int rankstd(int x) {
    int sum=0;
    for(int i=0;i<n;i++) 
        if(removed[i]==0&&stu[i].s[4]>stu[x].s[4]) sum++;
    return sum+1;
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
 
}void show_statistics() {
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
	printf("Number of students who failed all subjects: %d\n\n",num-sum[1]);
}

void printmenu() {
    printf("Welcome to Student Performance Management System (SPMS).\n\n"
            "A - Add\n"
            "B - Remove\n"
            "C - Query\n"
            "D - Show ranking\n"
            "E - Show Statistics\n"
            "Q - Exit\n\n");
}

int IsChoiceValid(char ch) {
    if((ch - 'A' <= 4 && ch - 'A' >= 0) || ch == 'Q')
        return 1;
    return 0;
}

void binSort() {
    printf("Please input class and subject,"
        "0 for all stucents and 0 for the whole score.\n"
        "1, 2, 3, 4 for %s, %s, %s and %s, and 0 for total score.\n"
        "(e.g. 114514114514 1 means class 114514114514 and subject %s)\n\n",
        subject[0],subject[1],subject[2],subject[3],
        subject[0]);

    int sbj;
    char stringc[15];
    scanf("%s%d",stringc,&sbj);

    sbj = (sbj == 0)? 4 : sbj-1;

    int rk[MAXN];
    memset(rk,0,sizeof(rk));
    int nrk = 0; 

    if(strcmp(stringc,"0")) {
        for(int i = 0;i < n;i++) 
            if(!strcmp(stu[i].cid,stringc) && !removed[i]) rk[nrk++] = i;
    }
    else {
        for(int i = 0;i < n;i++)
            if(!removed[i]) rk[nrk++] = i;
    }

    int mid,left,right,temp;

    for(int i = 1;i < nrk;i++) {
        left = 0;
        right = i - 1;
        temp = rk[i];
        while(left <= right) {
            mid = (left + right)/2;
            if(stu[temp].s[sbj] < stu[rk[mid]].s[sbj]) right = mid-1;
            else left = mid+1;
        }
        for(int j = i - 1;j >= left;j--) rk[j + 1] = rk[j];
        if(left != i) rk[left] = temp;
    }

    printf("Here is the ranklist of subject %s in class %s "
        "(0 for all students).\n"
        "class\trank\tsid\tname\tscore\n",subject[sbj],stringc);
    for(int i = nrk-1;i > -1;i--) 
        printf("%s\t%d\t%s\t%s\t%d\n",stringc,nrk-i,stu[rk[i]].sid,stu[rk[i]].nam,stu[rk[i]].s[sbj]);
    putchar('\n');
}

int main() {
    for(int i=0;i<MAXN;i++) {
        stu[i].passed=0;
    }
    for(;;) {
        printmenu();
        char choice = 0;
        scanf("%c",&choice);
        while(!IsChoiceValid(choice)) {
            char ch;
            // printf("Invalid input!\n");
            scanf("%c",&choice);
            while((ch = getchar())!='\n')
                ;
        }
        if(choice == 'A') add();
        else if(choice == 'B') rem(0);
        else if(choice == 'C') rem(1);
        else if(choice == 'D') binSort();
        else if(choice == 'E') show_statistics();
        else if(choice == 'Q') break;
    }
    return 0;
}