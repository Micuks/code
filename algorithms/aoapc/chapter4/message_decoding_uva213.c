#include<stdio.h>
#include<string.h>
char code[8][1<<8];
int readchar() {
    for(;;) {
        char ch=getchar();
        if(ch=='\n'||ch=='\r') ;
        else return ch;
    }
}
int readcodes() {
    memset(code,0,sizeof(code));
    code[1][0]=readchar();
    char ch;
    for(int i=2;i<8;i++) {
        for(int j=0;j<(1<<i)-1;j++) {
            ch=getchar();
            if(ch=='\n'||ch=='\r') return 1;
            if(ch==EOF) return 0;
            code[i][j]=ch;
        }
    }
    return 1;
}
int readint(int n) {
    int v=0;
    while(n--) v=v*2+readchar()-'0';
    return v;
}
void printcodes() {
    for(int len=1;len<8;len++) {
        for(int i=0;i<(1<<len)-1;i++) {
            if(code[len][i]=='\0') return;
            printf("code[%d][%d] = %c\n",len,i,code[len][i]);
        }
    }
}
int main() {
    while(readcodes()){
        // printcodes();
        for(;;) {
            int len=readint(3);
            if(len==0) break;
            for(;;) {
                int v=readint(len);
                if(v==(1<<len)-1) break;
                putchar(code[len][v]);
            }
        }
            putchar('\n');
    }
    return 0;
}