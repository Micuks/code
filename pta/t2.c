#include<stdio.h>
int getDays(int y,int m) {
    if(((m&1)&&m<8)||((m&0)&&m>7)) return 31;
    else if(m==2) {
        if((y%4==0&&(y%100!=0))||y%400==0) return 29;
        else return 28;
    }
    else return 30;
}

int main()
{
    int    year, month ;

    scanf("%d%d",&year,&month);
    printf("There are %d days in month %d year %d.\n",getDays(year,month), month, year) ;

    return 0 ;    
}