#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>	

int tianping(int *a,int *b,int *c,int *d)
{
	int a1,b1,c1,d1;
	*a=a1;
	*b=b1;
	*c=c1;
	*d=d1;	
	if(a1*b1==c1*d1&&a1!=0&&c1!=0)
	{
		return 1;
	}
	else if(a1*b1!=c1*d1&&a1!=0&&c1!=0)
	return 0;
	else if(a1=0&&c1!=0)
	{
		return tianping(a下面总质量,b,c,d);
	}
	else if(a1=!0&&c1=0)
	{
		return tianping(a,b,c下面总质量,d);
	}
	else if(a1=0&&c1=0)
	{
		return tianping(a下面总质量,b,c下面总质量,d);
	}	
}
int zongzhiliang(int *a,int *b,int *c,int *d)
{
	int a1,b1,c1,d1;
	*a=a1;
	*b=b1;
	*c=c1;
	*d=d1;
	
	if(a1=0&&c1!=0||a1!=0&&c1=0)
	{
		return zongzhiliang(a+1,b+1,c+1,d+1);
	}
	else if(a1=0&&c1=0)
	{
		return zongzhiliang(a+1,b+1,c+1,d+1)+zongzhiliang(a+2,b+2,c+2,d+2);
	}	
	else
	return (*a+*c);
 } 

int main ()
{
	int a[100]={0},b[100]={0},c[100]={0},d[100]={0};
	int n;
	scanf("%d",&n);
	
	
}
