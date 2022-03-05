#include<stdio.h>
// #include<string.h>
int isValid(char ch[]) {
    int alpha=0,number=0;
    // if(strlen(ch)!=5) return 0;
    for(int i=0;i<4;i++) {
        if(((ch[i]>='A'&&ch[i]<='Z')||(ch[i]>='a'&&ch[i]<='z'))&&ch[i]!='O'&&ch[i]!='I'&&ch[i]!='i'&&ch[i]!='o') alpha++;
        else if(ch[i]>='0'&&ch[i]<='9') number++;
        // printf("alpha = %d, number = %d\n",alpha,number);
    }
    if(number==2&&alpha==2&&(ch[4]>='0'&&ch[4]<='9')) return 1;
    else return 0;
}
void printCode(char ch[]) {
    for(int i=0;i<5;i++) {
        if(ch[i]>='a'&&ch[i]<='z') ch[i]=ch[i]-'a'+'A';
    }
    printf("yes:%s\n",ch);
}
int main() {
    int t;
    scanf("%d",&t);
    char ch[10];
    while(t--) {
        scanf("%s",ch);
        // printf("%s\n",ch);
        if(isValid(ch)) printCode(ch);
        else printf("no.\n");
    }
    return 0;
}