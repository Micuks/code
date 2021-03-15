#include<stdio.h>

void delcharfun(char *str,char ch);

int main()
{
    char    ch,str[110];

    scanf("%s",str);    //读入字符串 
    getchar();            //读取回车符号 
    scanf("%c",&ch);    //读入字符 
    delcharfun(str,ch);    //删除 
    printf("%s\n",str);    //输出删除后结果 
    return 0;    
}

void delcharfun(char* str,char ch) {
    int len=0;
    char *ptr=str;
    ptr--;
    while(*(++ptr)!='\0') len++; 
    // printf("len = %d\n",len);
    for(int i=0;i<len;i++) {
        if(*(str+i)==ch) {
            for(int j=i;j<len+1;j++) {
                *(str+j)=*(str+j+1);
            }
            len--;
            i--;
        }
    }
}