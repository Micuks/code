#include <stdio.h>
#include <stdlib.h>
int number[6][2];
int cmp(const void*a,const void*b);
void swap(int *a,int *b);
int main()
{
	while(scanf("%d %d",&number[0][0],&number[0][1])==2)
	{
		swap(&number[0][0],&number[0][1]);
		int i;
		for(i=1;i<6;i++)
		{
			scanf("%d %d",&number[i][0],&number[i][1]);
			swap(&number[i][0],&number[i][1]);
		}
		qsort(number,6,2*sizeof(int),cmp);
        for(int i=0;i<6;i++) {
            printf("%d %d\n",number[i][0],number[i][1]);
        }
		if(
		  number[0][0]==number[1][0]&&number[1][0]==number[2][0]&&number[2][0]==number[3][0]
		&&number[2][1]==number[3][1]&&number[3][1]==number[4][1]&&number[4][1]==number[5][1]
		&&number[0][1]==number[1][1]&&number[1][1]==number[4][0]&&number[4][0]==number[5][0]
		)
		printf("POSSIBLE\n");
		else printf("IMPOSSIBLE\n");
	}
	return 0;
}
int cmp(const void*a,const void *b)
{
	if(*(int*)a==*(int*)b)
		return ((int*)a)[1]-((int*)b)[1];
	return *(int*)a-*(int*)b;
}
void swap(int *a,int *b)
{
	if(*a>*b)
	{
		int temp=*a;
		*a=*b;
		*b=temp;
	}
}