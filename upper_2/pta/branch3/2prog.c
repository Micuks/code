#include<stdio.h>
#define UP temp-'A'
#define LO temp-'a'
int main() {
    char temp;
    int count[53];
    for(int i=0;i<53;i++) count[i]=0;
    while((temp=getchar())!='\n'&&temp!=EOF) {
        if(UP>-1&&UP<26) count[UP]++;
        if(LO>-1&&LO<26) count[26+LO]++;
    }
    for(int i=0;i<26;i++) {
        if(count[i]) printf("The character %c has presented %d times.\n",i+'A',count[i]);
    }
    for(int i=0;i<26;i++) {
        if(count[i+26]) printf("The character %c has presented %d times.\n",i+'a',count[i+26]);
    }
    return 0;
}