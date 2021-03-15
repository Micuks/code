#include<stdio.h>
#include<string.h>
#define maxn 100
char s[maxn],s2[maxn];
int win=0,lose=0;
int left,chance;
void guess(char ch) {
    for(int i=0;i<strlen(s);i++) {
        if(s[i]==ch) {
            s[i]=' ';
            left--;
        }
    }
    if(left==strlen(s)) chance--;
    if(!chance) lose=1;
    if(!left) win=1;
}
int main() {
    int rnd;
    while(scanf("%d%s%s",&rnd,s,s2)==3&&rnd!=-1) {
        win=lose=0;
        chance=7,left=strlen(s);
        printf("Round %d\n",rnd);
        for(int i=0;i<strlen(s2);i++) {
            guess(s2[i]);
            if(win||lose) break;
        }
        if(win) printf("You win.\n");
        else if(lose) printf("You lose.\n");
        else printf("You chickened out.\n");
    }
}