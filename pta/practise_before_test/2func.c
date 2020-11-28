#include <stdio.h>

//将只包含小写字母的字符串str中的元音字母复制到字符数组vowel,并返回元音字符的个数。
int getVowel(char str[],char vowel[]) {
    char ini[]={'a','e','i','o','u'};
    char str1[101];
    for(int i=0;i<101;i++) str1[i]=str[i];
    int len,n;
    if(*str=='\0') return 0;
    else {
        n=0;
        for(;str1[n]!='\0';n++) 
            ;
        str1[n-1]='\0';
        len=getVowel(str1,vowel);
    }
    for(int i=0;i<5;i++) {
        if(*(str+n-1-1)==ini[i]&&n-2>-1) {
            vowel[len++]=ini[i];
            vowel[len]='\0';
            // printf("str[] = %s, n = %d, str[n-2] = %c, vowel[%d] = %c, ini[i] = %c\n",str,n,str[n-2],len-1,vowel[len-1],ini[i]);
            break;
        }
    }
    return len;
}

int main()
{
    char    vowel[101] , str[101];//每个数组都至少要101个字节 
    int        len ;

    scanf("%s",str);    //读入字符串 
    len = getVowel(str,vowel);    //复制 
    if ( len > 0 ) printf("%d %s\n", len , vowel);    //输出复制后结果 
    else printf("%d\n", len);//仅输出长度 

    return 0;    
}