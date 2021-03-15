#include<stdio.h>
#include<stdlib.h>
void swap(int*,int*);
int cmp(const void*a,const void *b);
int main() {
    int w[15],l[15];
    for(int i=0;i<15;i++) {
        w[i]=0;
        l[i]=0;
    }
    while(scanf("%d%d",&w[0],&l[0])==2) {
        swap(&w[0],&l[0]);
        for(int i=1;i<6;i++) {
            scanf("%d%d",&w[i],&l[i]);
            swap(&w[i],&l[i]);
        }
        int num[6][2];
        for(int i=0;i<6;i++) {
            num[i][0]=w[i];
            num[i][1]=l[i];
        }
        qsort(num,6,2*sizeof(int),cmp);
        for(int i=0;i<6;i++) {
            w[5-i]=num[i][0];
            l[5-i]=num[i][1];   
        }
        if(w[0]==w[1]&&w[1]==w[2]&&w[2]==w[3]&&
            w[4]==w[5]&&w[5]==l[0]&&l[0]==l[1]&&
            l[2]==l[3]&&l[3]==l[4]&&l[4]==l[5]) 
            printf("POSSIBLE\n");
        else printf("IMPOSSIBLE\n");
        for(int i=0;i<15;i++) {
            w[i]=0;
            l[i]=0;
            num[i][0]=0;
            num[i][1]=0;
        }
    }
    return 0;
}
void swap(int*a,int*b) {
    if(*a<*b) {
        int temp=*a;
        *a=*b;
        *b=temp;
    }
}
int cmp(const void*a,const void *b)
{
	if(*(int*)a==*(int*)b)
		return ((int*)a)[1]-((int*)b)[1];
	return *(int*)a-*(int*)b;
}