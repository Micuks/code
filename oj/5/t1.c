#include<stdio.h>
int main() {
    int n;
    double result=0;
    double num[105];
    scanf("%d",&n);
    for(int i=0;i<n;i++) {
        scanf("%lf",num+i);
        result+=*(num+i);
        // printf("%f ",*(num+i));
    }
    // putchar('\n');
    printf("%.2f\n",result/n);
    return 0;
}