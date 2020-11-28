#include<stdio.h>
#include<string.h>
int isParenthesesmatch(char a[]) {
    char temp;
    int count=0,ptr=0;
    while((temp=a[ptr++])!='\n'&&temp!=' ') {
        // printf("temp = %c\t",temp);
        if(temp=='(') count++;
        if(temp==')') count--;
        // printf("count = %d\n",count);
        if(count<0) return -1;
    }
    if(0==count) return 0;
    else return -1;
}
int main() {
    char string[300];
    memset(string,' ',sizeof(string));
    scanf("%s",string);
    if(isParenthesesmatch(string)==0) printf("parentheres match!\n");
    else printf("parentheses do not match!\n");
    return 0;

}