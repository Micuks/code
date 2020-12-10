#include<stdio.h>
int main()
{
	int n,i,j;
	float a[100][3],b[6][5]={0};
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		for(j=0;j<3;j++)
		  scanf("%f",&a[i][j]);
	}
	//int k=1;
	for(i=0;i<n;i++)
	{
		if(a[i][0]==1)
		{
			if(a[i][1]==1)
			  b[0][0]+=a[i][2];
			else if(a[i][1]==2)
			  b[1][0]+=a[i][2]; 
			else if(a[i][1]==3)
			  b[2][0]+=a[i][2]; 
			else if(a[i][1]==4)
			  b[3][0]+=a[i][2]; 
			else if(a[i][1]==5)
			  b[4][0]+=a[i][2]; 
		}
	    else if(a[i][0]==2)
		{
			if(a[i][1]==1)
			  b[0][1]+=a[i][2];
			else if(a[i][1]==2)
			  b[1][1]+=a[i][2]; 
			else if(a[i][1]==3)
			  b[2][1]+=a[i][2]; 
			else if(a[i][1]==4)
			  b[3][1]+=a[i][2]; 
			else if(a[i][1]==5)
			  b[4][1]+=a[i][2]; 
		}
		else if(a[i][0]==3)
		{
			if(a[i][1]==1)
			  b[0][2]+=a[i][2];
			else if(a[i][1]==2)
			  b[1][2]+=a[i][2]; 
			else if(a[i][1]==3)
			  b[2][2]+=a[i][2]; 
			else if(a[i][1]==4)
			  b[3][2]+=a[i][2]; 
			else if(a[i][1]==5)
			  b[4][2]+=a[i][2]; 
		}
		else if(a[i][0]==4)
		{
			if(a[i][1]==1)
			  b[0][3]+=a[i][2];
			else if(a[i][1]==2)
			  b[1][3]+=a[i][2]; 
			else if(a[i][1]==3)
			  b[2][3]+=a[i][2]; 
			else if(a[i][1]==4)
			  b[3][3]+=a[i][2]; 
			else if(a[i][1]==5)
			  b[4][3]+=a[i][2]; 
		}
	}
	for(i=0;i<5;i++)
	{
		b[i][4]=b[i][0]+b[i][1]+b[i][2]+b[i][3];
	}
	for(j=0;j<5;j++)
	  b[5][j]=b[0][j]+b[1][j]+b[2][j]+b[3][j]+b[4][j];
	
	//printf("\tsaler1\tsaler2\tsaler3\tsaler4\ttotal\n");
	
	for(i=0;i<6;i++)
	{
//		if(i+1!=6)
//		  printf("prod%d\t",i+1);
//		else
//		  printf("total\t");
		for(j=0;j<5;j++)
		    printf("%.1f\t",b[i][j]);
		printf("\n");
	}
	return 0;
}