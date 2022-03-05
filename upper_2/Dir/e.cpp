#include <cstdio>
void getdegree(int& a, int& d, int& inv) {
    char ch;
    d = 0;
    while((ch = getchar()) != '-' && ch != '+' && ch != '\n' && ch != EOF) {
        if(ch <= '9' && ch >= '0') {
            d = d * 10 + (ch - '0');
        }
    }
    if(ch == '-' || ch == '+') {
        ungetc(ch, stdin);
    }
    if(a == 0) {
        a = 1;
    }
    //printf("\ninv = %d, a = %d, d = %d\n", inv, a, d);
    if(inv)
        putchar('-');
    else putchar('+');
    if(d == 0)
        printf("%d", a);
    else if(d == 1) {
        printf("%d", a*d);
    }
    else if(d == 2) {
        printf("%dx", a*d);
    }
    else {
        printf("%dx^%d", a*d, d-1);
    }
    a = 0, d = 0, inv = 0;
}

int main() {
    char ch;
    while((ch = getchar()) != '=') {
        ;
    }
    printf("f'(x)=");
    ch = getchar();
    char och = ch;
    if(ch >= '0' && ch <= '9') {
        if(ch = getchar()) == '\n' || ch == EOF) {
            putchar('0');
        }
    }
    ungetc(och, stdin);
    ungetc(ch, stdin);
    int a = 0, d = 0, inv = 0;// if(a == 0) a = 1;
    while((ch = getchar()) != '\n' && ch != EOF) {
        //printf("%c\n", ch);
        if(ch == 'x') {
            getdegree(a, d, inv);
        }
        else if(ch <= '9' && ch >= '0') {
            a = a * 10 + (ch - '0');
        }
        else if(ch == '-') {
            inv = 1;
        }
        else {
            inv = 0;
        }
    }
    putchar('\n');
    return 0;
}
