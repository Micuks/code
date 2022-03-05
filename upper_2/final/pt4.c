#include<stdio.h>
typedef struct{
    int opr;
    int bianhao;
    int flag;
    char name[20];
    char num[20];
    int y;
    int m;
    int d;
}ST;
int add(ST *ptr[], int bianhao,int i,ST a[], int c);
int main() {
    int n;
    ST book[205];
    ST* ptr[205];
    for(int i=0;i<n;i++) book[i].flag=0;
    scanf("%d",&n);
    for(int i=0;i<n;i++) {
        scanf("%s%s%d%d%d",book[i].name,book[i].num,&book[i].y,&book[i].m,&book[i].d);
        book[i].bianhao=i;
        book[i].opr=1;
        book[i].flag=1;
    }
    int t;
    int c=n;
    scanf("%d",&t);
    for(int i=0;i<t;i++) {
        scanf("%d",&book[n+i].opr);
        if(book[n+i].opr==1)
            scanf("%d%s%s%d%d%d",&book[n+i].bianhao,book[n+i].name,book[n+i].num,&book[n+i].y,&book[n+i].m,&book[n+i].d);
        if(book[n+i].opr==2) scanf("%d",&book[n+i].bianhao);
    }
    t++;
    book[t-1].bianhao=205;
    book[t-1].opr=1;
    book[t].bianhao=205;
    book[t].opr=1;
    for(int i=0;i<n+t;i++) {
        // printf("%d %d %d %s %s %d %d %d\n",book[i].opr,book[i].flag,book[i].bianhao,book[i].name,book[i].num,book[i].y,book[i].m,book[i].d);
    }

    for(int i=0;i<n+t;i++) {
        if(book[i].opr==1) {
            c=add(ptr,book[i].bianhao,i,book,c);
        }
        if(book[i].opr==2) {
            for(int j=book[i].bianhao;j<c;j++) {
                ptr[j]=ptr[j+1];
            }
            c--;
        }
    }
    // printf("c=%d\n",c);
            // printf("%d %s %s %d %d %d\n",5,ptr[5]->name,ptr[5]->num,ptr[5]->y,ptr[5]->m,ptr[5]->d);

    for(int i=0;i<c;i++) {
        printf("%d %s %s %d %d %d\n",i,ptr[i]->name,ptr[i]->num,ptr[i]->y,ptr[i]->m,ptr[i]->d);
    }
    return 0;
}
int add(ST *ptr[], int bianhao,int i,ST a[], int c) {
        if(a[i].flag==0) c++;
        ptr[bianhao] = &a[i];
        a[i].flag=1;
    return c;
}
