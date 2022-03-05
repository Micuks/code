#include<stdio.h>
int main() {
    int n,mt,nt;
    double temp;
    scanf("%d",&n);
    float matrix[6][5];
    for(int i=0;i<6;i++) 
        for(int j=0;j<5;j++) matrix[i][j]=0;
    while(n--) {
        scanf("%d%d%lf",&nt,&mt,&temp);
        matrix[mt-1][nt-1]+=temp;
        matrix[mt-1][4]+=temp;
        matrix[5][nt-1]+=temp;
        matrix[5][4]+=temp;
    }
    for(int i=0;i<6;i++) {
        for(int j=0;j<5;j++) {
            printf("%.1f\t"/* +!j */,matrix[i][j]);
            // printf("\t%.1f"+!j,matrix[i][j]);
        }
        putchar('\n');
    }
        return 0;
}