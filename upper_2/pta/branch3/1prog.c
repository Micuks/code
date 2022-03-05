#include<stdio.h>
#include<string.h>
int main() {
    char string[300];
    memset(string,' ',sizeof(string));
    scanf("%s",string);
    int count=0,ptr=0,flag=0;
    while(string[ptr]!='\n'&&string[ptr]!=' ') {
        // for(;ptr<100;ptr++) {
        if(string[ptr]=='(') count++;
        if(string[ptr]==')') count--;
        if(count<0) flag=1;
        ptr++;
    }
    if(count==0&&!flag) printf("parentheses match!\n");
    else printf("parentheses do not match!\n");
    return 0;
}