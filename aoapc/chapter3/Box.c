#include<stdio.h>
int the_function_which_is_used_to_operate_the_little_things(int*a,int*times,int l,int flag,int ptr);
int judge2(int length,int*a,int*times,int*l,int*w);
int main() {
    int a[150],times[150];
    int l[150],w[150],count=0;
    int io=0;
    int ptr=0;
    for(int i=0;i<150;i++) {
        a[i]=0;
        times[i]=0;
    }
    while(scanf("%d%d",&l[io],&w[io])==2) {
        // printf("io = %d\n%d %d\n",io,l[io],w[io]);
        int flag=1;
        ptr=the_function_which_is_used_to_operate_the_little_things(a,times,l[io],flag,ptr);
        ptr=the_function_which_is_used_to_operate_the_little_things(a,times,w[io],flag,ptr);
        count+=2;
        if(count==12) {
            // printf("io = %d\n",io);
            // for(int i=0;i<=io;i++) printf("%d %d\n",l[i],w[i]);
            count=0;
            flag=1;
            if(ptr==3) {
                for(int i=0;i<3;i++) {
                    if(times[i]!=4) flag=0;
                    if(l[i]==w[i]) flag=0;
                }
            }
            else if(ptr==2) {
                if(times[0]%4!=0||times[1]%4!=0) flag=0;
                if(times[0]>times[1]) flag=judge2(1,a,times,l,w);
                else flag=judge2(0,a,times,l,w);
            }
            else if(ptr==1) {
                ;
            }
            else flag=0;
            if(flag) printf("POSSIBLE\n");
            else printf("IMPOSSIBLE\n");
            ptr=0;
            for(int i=0;i<150;i++) {
                a[i]=0;
                times[i]=0;
            }
            io=-1;
        }
        io++;
    }
    return 0;
}
int the_function_which_is_used_to_operate_the_little_things(int*a,int*times,int l,int flag,int ptr){
    for(int i=0;i<3;i++) {
        if(a[i]==l) {
            times[i]++;
            flag=0;
        }
    }
    if(flag) {
        a[ptr]=l;
        times[ptr++]++;
    }
    return ptr;
}
int judge2(int length,int*a,int*times,int*l,int*w) {
    for(int i=0;i<6;i++) {
        if(l[i]==length&&w[i]==length) return 0;
    }
    return 1;
}