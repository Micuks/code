#include<iostream>
#include<cmath>
#include<string.h>
#include<stdlib.h>
// #include<conio.h>
using namespace std;

//数据系统 
struct student
{
	int NO;
	string name;
	int math;
	int english;
	int cpp;
	struct student *neXt;
};

//定义一些变量，输出内容，并打开文件 
const char *path="D:\\学生成绩管理系统.tXt";
FILE *fp=fopen(path,"w+");
string ment="学号\t姓名\t数学成绩\t英语成绩\t计导成绩"; 
    
student *newdata=new student;
student *head=newdata,*p=head;
	
//成绩录入************************************************
void enter(void)
{
	cout<<"请输入学生信息："<<endl;
	cout<<"学号：";
	cin>>p->NO;
	cout<<"姓名：";
	cin>>p->name;
	cout<<"数学成绩：";
	cin>>p->math;
	cout<<"英语成绩：";
	cin>>p->english;
	cout<<"计导成绩：";
	cin>>p->cpp;
	cout<<"是否结束输入(输入0结束,输入1继续)"<<endl;
	
	char ch;                                     //判断是否结束输入 
	if((ch=getchar())=='0')
	{
		p->neXt=NULL;
		return;
	}
	else if(ch=='1')
	{
		p->neXt=new student;
		p=p->neXt;
		p->neXt=NULL;
		enter();
	}	
} 
//成绩修改*****************************************************
void change(void)
{
	cout<<"输入需要修改的学生的学号"<<endl;
	int a;
	cin>>a;
	p=head;
	while(p!=NULL)
	{
		if(p->NO==a)                           //判断是否找到目标学生 
		{
			cout<<"请输入需要修改的学生信息："<<endl;
	        cout<<"姓名：";
	        cin>>p->name;
	        cout<<"数学成绩：";
	        cin>>p->math;
	        cout<<"英语成绩：";
	        cin>>p->english;
        	cout<<"计导成绩：";
	        cin>>p->cpp;
	        return;
		}
		else
		{
			p=p->neXt;
		}
	} 
} 

//添加*********************************************
void add(void)
{
	p=head;
	while(p->neXt!=NULL)
	{
		p=p->neXt;
	}
	p->neXt=new student;
	p=p->neXt;
	cout<<"请输入新添加的学生信息："<<endl;
	cout<<"学号：";
	cin>>p->NO;
	cout<<"姓名：";
	cin>>p->name;
	cout<<"数学成绩：";
	cin>>p->math;
	cout<<"英语成绩：";
	cin>>p->english;
	cout<<"计导成绩：";
	cin>>p->cpp;
	return;
} 
 
//删除********************************************
void rem0ve(void)
{
	cout<<"输入需要删除的学生的学号"<<endl;
	int a;
	cin>>a;
	p=head;
	student *q;
	q=head;
	int j=0;
	while(p->NO!=a)
	{
		p=p->neXt;
		j++;
	}
	if(j!=0)
	{
	    for(int i;i<j-1;i++)
	    {
		    q=q->neXt;
	    }
	    q->neXt=p->neXt;
	    p->neXt=NULL;
	}
	else if(j==0)
	{
		head=p->neXt;
	}
	return;
}

//查询统计*****************************
//学号查询 
void seekNO(void)
{
	cout<<"输入需要查询的学生的学号"<<endl;
	int a;
	cin>>a;
	p=head;
	while(p!=NULL)
	{
		if(p->NO==a)
		{
			cout<<"学号："<<p->NO<<endl;
	        cout<<"姓名："<<p->name<<endl;
	        cout<<"数学成绩："<<p->math<<endl;
	        cout<<"英语成绩："<<p->english<<endl;
        	cout<<"计导成绩："<<p->cpp<<endl;
	        return;
		}
		else
		{
			p=p->neXt;
		}
	} 
} 
//姓名查询
 void seekname(void)
{
	cout<<"输入需要查询的学生的名字"<<endl;
	char a[50];
	int i=0;
	char ch;
	while((ch=getchar())!='\r') 
	{
		a[i]=ch;
		i++;
	}
	a[i]='\0';
	p=head;
	while(p!=NULL)
	{
		if(p->name.compare(a)==0)
		{
			cout<<"学号："<<p->NO<<endl;
	        cout<<"姓名："<<p->name<<endl;
	        cout<<"数学成绩："<<p->math<<endl;
	        cout<<"英语成绩："<<p->english<<endl;
        	cout<<"计导成绩："<<p->cpp<<endl;
	        return;
		}
		else
		{
			p=p->neXt;
		}
	} 
} 

//按照成绩查询
void seekmath(void)
{
	p=head;
	cout<<"数学成绩："<<endl;
	while(p!=NULL)
	{
		cout<<"学号："<<p->NO<<",姓名："<<p->name<<",数学成绩："<<p->math<<endl;
		p=p->neXt;
	} 
	return;
} 
void seekenglish(void)
{
	p=head;
	cout<<"英语成绩："<<endl;
	while(p!=NULL)
	{
		cout<<"学号："<<p->NO<<",姓名："<<p->name<<",英语成绩："<<p->english<<endl;
		p=p->neXt;
	} 
	return;
} 
void seekcpp(void)
{
	p=head;
	cout<<"计导成绩："<<endl;
	while(p!=NULL)
	{
		cout<<"学号："<<p->NO<<",姓名："<<p->name<<",计导成绩："<<p->cpp<<endl;
		p=p->neXt;
	} 
	return;
} 

//分数段统计
//(暂略) 

//菜单
void menu4(void)
{
	cout<<"***********************************"<<endl;
		cout<<"选择需要统计的科目"<<endl;
	    cout<<"1.数学"<<endl;
	    cout<<"2.英语"<<endl;
	    cout<<"3.计导"<<endl;
	    char ch7;
		if((ch7=getchar())=='1')
		{
			p=head;
			int a=0,b=0,c=0,d=0,e=0;
			while(p!=NULL) 
			{
			if(p->math>=90)
			a++;
			if(p->math>=80&&p->math<90)
			b++;
			if(p->math>=70&&p->math<80)
			c++;
			if(p->math>=60&&p->math<70)
			d++;
			if(p->math<60)
			e++;
			p=p->neXt;
		    }
			cout<<"数学成绩在90分及以上的人数："<<a<<endl; 
			cout<<"数学成绩在80到90分的人数："<<b<<endl; 
			cout<<"数学成绩在70到80分的人数："<<c<<endl; 
			cout<<"数学成绩在60到70分的人数："<<d<<endl; 
			cout<<"数学成绩在60分以下的人数："<<e<<endl; 
		 } 
		 else if(ch7=='2')
		 {
		 	p=head;
			int a=0,b=0,c=0,d=0,e=0;
			while(p!=NULL)
			{
			if(p->english>=90)
			a++;
			if(p->english>=80&&p->english<90)
			b++;
			if(p->english>=70&&p->english<80)
			c++;
			if(p->english>=60&&p->english<70)
			d++;
			if(p->english<60)
			e++;
			p=p->neXt;
		}
			cout<<"英语成绩在90分及以上的人数："<<a<<endl; 
			cout<<"英语成绩在80到90分的人数："<<b<<endl; 
			cout<<"英语成绩在70到80分的人数："<<c<<endl; 
			cout<<"英语成绩在60到70分的人数："<<d<<endl; 
			cout<<"英语成绩在60分以下的人数："<<e<<endl; 
		 }
		 else if(ch7=='3')
		 {
		 	p=head;
			int a=0,b=0,c=0,d=0,e=0;
		    while(p!=NULL)
		    {
			if(p->cpp>=90)
			a++;
			if(p->cpp>=80&&p->cpp<90)
			b++;
			if(p->cpp>=70&&p->cpp<80)
			c++;
			if(p->cpp>=60&&p->cpp<70)
			d++;
			if(p->cpp<60)
			e++;
			p=p->neXt;
		}
			cout<<"计导成绩在90分及以上的人数："<<a<<endl; 
			cout<<"计导成绩在80到90分的人数："<<b<<endl; 
			cout<<"计导成绩在70到80分的人数："<<c<<endl; 
			cout<<"计导成绩在60到70分的人数："<<d<<endl; 
			cout<<"计导成绩在60分以下的人数："<<e<<endl; 
		 }
}

void menu3(void)
{
	cout<<"***********************************"<<endl;
			cout<<"输入序号选择选项"<<endl;
	        cout<<"1.查询数学成绩"<<endl;
	        cout<<"2.查询英语成绩"<<endl;
	        cout<<"3.查询计导成绩"<<endl;
	        char ch3;
			if((ch3=getchar())=='1')
			seekmath();
			else if(ch3=='2')
			seekenglish();
		    else if(ch3=='3')
			seekcpp(); 
			cout<<"是否继续查询（1继续，0返回上一级）"<<endl;
			char ch5;
			if((ch5=getchar())=='1')
			menu3();
			else if(ch5=='0')
			return;
} 
void menu2(void)
 {
 	cout<<"***********************************"<<endl;
		cout<<"输入序号选择选项"<<endl;
	    cout<<"1.按学号查询"<<endl;
	    cout<<"2.按姓名查询"<<endl;
	    cout<<"3.按成绩查询"<<endl;
	    cout<<"4.按分数段统计人数"<<endl; 
	    char ch2;
		if((ch2=getchar())=='1')
		seekNO();
		else if(ch2=='2')
		seekname();
		else if(ch2=='3')
		{
			menu3();
		}
		else if(ch2=='4')
		{
			menu4();
		}
		cout<<"是否继续查询（1继续，0返回主菜单）"<<endl;
		char ch6;
		if((ch6=getchar())=='1')
		menu2();
		else if(ch6=='0')
		return;
 }
 
void menu(void)
{
	cout<<"***********************************"<<endl;
	cout<<"输入序号选择选项"<<endl;
	cout<<"1.成绩录入"<<endl;
	cout<<"2.修改"<<endl;
	cout<<"3.添加"<<endl;
	cout<<"4.删除"<<endl;
	cout<<"5.查询统计"<<endl;
	cout<<"6.退出程序"<<endl;
	char ch;
	if((ch=getchar())=='1')
	enter();
	else if(ch=='2')
	change();
	else if(ch=='3')
	add();
	else if(ch=='4')
	rem0ve();
	else if(ch=='5')
	{
		menu2();
	}
	else if(ch=='6')
	return;
	cout<<"是否返回主菜单（1表示返回/0表示结束）"<<endl;
	char ch4;
	if((ch4=getchar())=='1')
	menu();
	else if(ch4=='0')
	return;
} 
 
 
int main()
{
	cout<<"欢迎使用宇宙无敌超级学生成绩管理系统！"<<endl<<endl;
	menu();
	cout<<endl<<"感谢帅气迷人风度翩翩的您的使用！"<<endl;
	p=head;
	while(p!=NULL)
	{
	    fprintf(fp,"%s\n",ment.c_str());
	    fprintf(fp,"%d\t",p->NO);
	    fprintf(fp,"%s\t",p->name.c_str());
	    fprintf(fp,"%d\t",p->math);
	    fprintf(fp,"%d\t",p->english);
	    fprintf(fp,"%d\n",p->cpp);
	    p=p->neXt;
    }
	fclose(fp);
	return 0;
}










