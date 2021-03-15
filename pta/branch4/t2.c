#include <stdio.h>
char *locatesubstr(char *str1, char *str2);
int main()
{
    char str1[505], str2[505];
    char *p;
    // gets(str1);
    // gets(str2);
    p = locatesubstr(str1, str2);

    if (p == NULL)
        printf("NULL!\n");
    else
        puts(p);

    return 0;
}
char* locatesubstr(char* str1,char* str2) {
    int ptr=-1,len1=0,len2=0;
    while(str1[++ptr]!='\0') len1++;
    ptr=-1;
    int flag=0;
    int i;
    while(str2[++ptr]!='\0') len2++;
//     printf("len1 = %d, len2 = %d\n",len1,len2);
    int count=0;
    for(i=0;i<len1;i++) {
//         printf("str1[i] = %c,count = %d,str2[count] = %c\n",str1[i],count,str2[count]);
        if(str1[i]==str2[count]) count++;
        else {
            if(count) i-=count;
            count=0;
        }
        if(count==len2) {
            flag=1;
            break;
        }
    }
//     printf("flag = %d,i=%d\n",flag,i);
    if(flag) return str1+i+1-len2;
    else return NULL;
}