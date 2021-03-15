#include<stdio.h>
#include<math.h>
#include<string.h>
const double eps=1e-6;
long long powerfunction(int base,int power) {
    long long result=1;
    while(power) {
        if(power&1) result=1ll*result*base;
        base=1ll*base*base;
        power>>=1;
    }
    return result;
}
void process(double a,int b,int* pe,int* pm) {
    int e=0,m=0,m1;
    for(m=0;m<=9;m++) {
        m1=powerfunction(2,m+1);
        int temp=round(log10((b+log10(a)-log10(m1-1))/log10(2)+m+2)/log10(2));
        if(fabs((1<<temp)-((b+log10(a)-log10(m1-1))/log10(2)+m+2))<eps) {
            e=temp;
            break;
        }
    }
        *pe=e;
        *pm=m;
}
int main() {
    int e,m,b;
    double a;
    char string[100];
    while(scanf("%s",string)==1&&strcmp(string,"0e0")!=0) {
        int len=strlen(string);
        *strchr(string,'e')=' ';
        sscanf(string,"%lf%d",&a,&b);
        process(a,b,&e,&m);
        printf("%d %d\n",m,e);
    }
    return 0;
}