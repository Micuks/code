#include<stdio.h>
int fastpow_mod_11(int base,int power) {
    long long result=1;
    while(power) {
        if(power&1) result=result*base%11;
        power>>=1;
        base=1ll*base*base%11;
    }
    return result%11;
}
int calculate_the_last_number(int code[]) {
    long long result=0;
    for(int i=0;i<17;i++) {
        result+=fastpow_mod_11(2,i+1)*code[16-i];
        result%=11;
    }
    return (12-result)%11;
}
int main() {
    char strcode;
    int code[25];
    int n;
    scanf("%d",&n);
    while(n--) {
        while((strcode=getchar())=='\n')
            ;
        ungetc(strcode,stdin);
        for(int i=0;i<18;i++) {
            ((strcode=getchar())=='X')?(code[i]=10):(code[i]=strcode-'0');
            // printf("%d",code[i]);
        }
        // printf("\ncalculate_the_last_number(code) = %d\n",calculate_the_last_number(code));
        if(calculate_the_last_number(code)==code[17]) printf("right\n");
        else printf("wrong\n");
    }
    return 0;
}