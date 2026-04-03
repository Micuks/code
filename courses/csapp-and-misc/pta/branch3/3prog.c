#include<stdio.h>
#include<string.h>
#include<ctype.h>
int main() {
    char instr[105];
    char pwbet[60];
    scanf("%s",instr);
    scanf("%s",pwbet);
    pwbet[26]=pwbet[0];
    scanf("%s",pwbet+27);
    pwbet[53]=pwbet[27];//pwbet[0]~pwbet[26] Upper alphabet;pwbet[27]~pwbet[53] Lower alphabet;
    int len=strlen(instr);
    for(int i=0;i<len;i++) {
        if(isupper(instr[i])) printf("%c",pwbet[instr[i]-'A'+1]);
        else printf("%c",pwbet[27+instr[i]-'a'+1]);
    }
    putchar('\n');
    return 0;
}