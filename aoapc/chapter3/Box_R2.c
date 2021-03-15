#include<stdio.h>
void swap(int*,int*);
void sort(int*,int*);
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
        sort(w,l);
        // for(int i=0;i<6;i++)    printf("%d %d\n",w[i],l[i]);
        if(w[0]==w[1]&&w[1]==w[2]&&w[2]==w[3]&&
            w[4]==w[5]&&w[5]==l[0]&&l[0]==l[1]&&
            l[2]==l[3]&&l[3]==l[4]&&l[4]==l[5]) 
            printf("POSSIBLE\n");
        else printf("IMPOSSIBLE\n");
        for(int i=0;i<15;i++) {
            w[i]=0;
            l[i]=0;
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
void sort(int*w,int*l) {
    int temp;
    for(int i=0;i<5;i++) {
        for(int j=5;j>i;j--) {
            if(w[j]==w[j-1]) {
                if(l[j]>l[j-1]) {
                    temp=l[j];
                    l[j]=l[j-1];
                    l[j-1]=temp;
                }
            }
            else if(w[j]>w[j-1]) {
                temp=w[j];
                w[j]=w[j-1];
                w[j-1]=temp;
                temp=l[j];
                l[j]=l[j-1];
                l[j-1]=temp;
            }
        }
    }
}