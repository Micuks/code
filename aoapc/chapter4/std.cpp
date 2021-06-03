#include<cstdio>
#include<cstring>
const char sub[5][20]={"","Chinese","Mathematics","English","Programming"};
const double eps=1e-5;//eps是double类型 
int cmd;
int sco[200][5],cid[200],n;//cid只是不超过20这个正整数,不是20位cid 
char sid[200][15],name[200][15];
void add()
{
	for(;;)
	{
		printf("Please enter the SID, CID, name and four scores. Enter 0 to finish.\n");
		scanf("%s",sid[n]);
		if(!strcmp(sid[n],"0"))return ;//单个0的第二个字符是'\0' (前提:sid保证是10位数)
		scanf("%d%s",&cid[n],name[n]);
		for(int i=1;i<=4;i++)
			scanf("%d",&sco[n][i]),sco[n][0]+=sco[n][i];
		for(int i=0;i<n;i++)
			if(cid[i]&&(!strcmp(sid[i],sid[n]))){printf("Duplicated SID.\n");sco[n][0]=cid[n]=0;break;}
		//cid清零是为了后面用来判断学生是否已被删除 
		//注意这里也要判断cid[i]是否为0(该学生是否被删除),我因为这个地方被卡了很久 
		if(cid[n])n++;
	}
}
int rank(int x)
{
	int sum=0;
	for(int i=0;i<n;i++)
		if(cid[i]&&sco[i][0]>sco[x][0])sum++;
	return sum+1;//sum是分数比他高的人,要加1 
}
void rq(int cmd)
{
	char id[15];
	for(;;)
	{
		printf("Please enter SID or name. Enter 0 to finish.\n");
		scanf("%s",id);
		if(!strcmp(id,"0"))return ;
		int cnt=0;
		for(int i=0;i<n;i++)
		{
			if(cid[i]&&(!strcmp(id,sid[i])||!strcmp(id,name[i])))
			{
				if(cmd==2)cid[i]=0,cnt++;
				else
				{
					printf("%d %s %d %s ",rank(i),sid[i],cid[i],name[i]);
					for(int j=1;j<=4;j++)printf("%d ",sco[i][j]);
					printf("%d %.2lf\n",sco[i][0],sco[i][0]/4.0+eps);//注意是4.0，并且要加一个eps 
				}
				if(id[0]>='0'&&id[0]<='9')break;//sid第一个字符一定是数字,而名字第一个字符一定是大写字母 
				//输入的是sid且已找到，直接退出 
			}
		}
		if(cmd==2)printf("%d student(s) removed.\n",cnt);
	}
}
void show_statistics()
{
	printf("Please enter class ID, 0 for the whole statistics.\n");
	int pass[5]={},sum[5]={},num=0;//sum[i]:通过i科的人数;num:统计的总人数;pass[i]通过科目i的人数 
	int tot[5]={};//单科所有学生的总分 
	int id;
	scanf("%d",&id);
	for(int i=0;i<n;i++)
	{
		if(cid[i]&&(!id||cid[i]==id))
		{
			num++;
			int cnt=0;
			for(int j=1;j<=4;j++)
			{
				tot[j]+=sco[i][j];
				if(sco[i][j]>=60)pass[j]++,sum[++cnt]++;//提前累加好，不用再做前缀和处理 
			}
		}
	}
	for(int i=1;i<=4;i++)
	{
		printf("%s\n"
		"Average Score: %.2lf\n"
		"Number of passed students: %d\n"
		"Number of failed students: %d\n\n",sub[i],(double)tot[i]/(double)num+eps,pass[i],num-pass[i]);
	}
	printf("Overall:\n"
	"Number of students who passed all subjects: %d\n",sum[4]);
	for(int i=3;i;i--)
		printf("Number of students who passed %d or more subjects: %d\n",i,sum[i]);
	printf("Number of students who failed all subjects: %d\n\n",num-sum[1]);//一科都没有通过的人,利用容斥原理 
}
int main()
{
	//freopen("output.out","w",stdout);//一定要删文件读写! 
	for(;;)
	{
		printf("Welcome to Student Performance Management System (SPMS).\n\n"
		"1 - Add\n"
		"2 - Remove\n"
		"3 - Query\n"
		"4 - Show ranking\n"
		"5 - Show Statistics\n"
		"0 - Exit\n\n");
		scanf("%d",&cmd);
		switch (cmd)
		{
			case 0:return 0;
			case 1:add();break;
			case 2:case 3:rq(cmd);break;
			case 4:printf("Showing the ranklist hurts students' self-esteem. Don't do that.\n");break; 
			case 5:show_statistics();break;
		}
	}
}