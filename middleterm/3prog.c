#include<stdio.h>
#include<string.h>
int strchange(char string[],int len,int ptr) {
    char news[110];
    for(int i=0;i<len;i++) news[i]=string[i];
    int count=0;
    char temp;
    if(news[ptr]==news[ptr-1]) {
        while(news[ptr]==news[ptr-1]&&news[ptr]==news[ptr-1]) {
            for(int i=ptr;i<len-1;i++) {
                news[i]=news[i+1];
            }
            news[len-1]='\0';
            count++;
            len--;
        }
        while(news[ptr]==news[ptr-1]&&news[ptr-1]==news[ptr-1]) {
            for(int i=ptr;i<len-1;i++) {
                news[i]=news[i+1];
            }
            news[len-1]='\0';
            count++;
            len--;
        }
        for(int i=ptr;i<len-1;i++) news[i]=news[i+1];
        news[len-1]='\0';
        count++;
        len--;
    }
    for(int i=0;i<len+count;i++) string[i]=news[i];
    // printf("count = %d\n",count);
    if(count) return count+strchange(string,len,ptr);
    else return 0;
}
int main() {
    char color;
    char string[110];
    int ptr,count;
    scanf("%c %d %s",&color,&ptr,string);
    // printf("%c %d %s",color,ptr,string);
    int len=strlen(string);
    for(int i=len-1;i>ptr;i--) {
        string[i]=string[i-1];
    }
    string[ptr]=color;
    count=strchange(string,len,ptr);
    if(count==len) printf("win\n");
    else printf("%s\n",string);
}