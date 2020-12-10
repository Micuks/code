#include<stdio.h>
int main() {
    int n,m,flag=1,isvalid;
    double temp;
    double num[1005];
    scanf("%d",&n);
    for(int i=0;i<n;i++) {
        scanf("%lf",num+i);
                // printf("%lf ",num+i);
    }
                // putchar('\n');
    scanf("%d",&m);
    for(int i=0;i<m;i++) {
        flag=1;
        isvalid=1;
        if(m==1) isvalid=0;
        scanf("%lf",&temp);
                // printf("%lf\n",temp);
        if(temp-(int)temp) isvalid=0;
        if(isvalid) {
            if(num[0]==temp) {
                printf("%.0lf\n",num[1]);
                flag=0;
            }
            for(int j=1;j<n-1;j++)
                if(num[j]==temp) {
                    printf("%.0lf %.0lf\n",num[j-1],num[j+1]);
                    flag=0;
                }
            if(num[n-1]==temp) {
                printf("%.0lf\n",num[n-2]);
                flag=0;
            }
        }
        if(flag) printf("NULL\n");
    }
    return 0;
}