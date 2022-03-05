#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main() {
    int n;
    scanf("%d",&n);
    int** a=(int**)malloc(n*sizeof(int*));
    for(int i=0;i<n;i++)
        a[i]=(int*)malloc(n*sizeof(int));
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%d",&a[i][j]);
    char opr[100];
    int head;
    int len=1;
    int sx,sy;
    int score=0;
    scanf("%s%d%d",opr,&sx,&sy);
    int times=strlen(opr);
    for(int i=0;i<times;i++) {
        if(opr[i]=='2') {
            head=2;
            sx--;
            score+=a[sx][sy];
        }
        if(opr[i]=='4') {
            head=4;
            sy--;
            score+=a[sx][sy];
        }
        if(opr[i]=='6') {
            head=6;
            sy++;
            score+=a[sx][sy];
        }
        if(opr[i]=='8') {
            head=8;
            sx++;
            score+=a[sx][sy];
        }
        if(a[sx][sy]) len++;
    }
    printf("%d %d\n%d %d\n",sx,sy,len,score);
    return 0;
}