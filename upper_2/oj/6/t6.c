#include<stdio.h>
#include<string.h>
int main() {
    char str1[105],str2[105];
    char ch;
    memset(str1,'\0',sizeof(str1));
    memset(str2,'\0',sizeof(str2));
    for(int i=0;(ch=getchar())!='\n';i++) {
        // printf("i = %d\t",i);
        str1[i]=ch;
        // str1[i+1]='\0';
    }
    for(int i=0;(ch=getchar())!='\n'&&ch!=EOF;i++) {
        str2[i]=ch;
        // str2[i+1]='\0';
    }
            // printf("str1[1] = %c, str2[1] = %c\n",str1[0],str2[0]);
            // printf("str1 = %s\nstr2 = %s\n",str1,str2);
    int len1=strlen(str1);
    int len2=strlen(str2);
    int temp=0,count=0;
    for(int i=0;i<len1;i++) {
        if(str1[i]==str2[temp]) temp++;
        else {
            temp=0;
        }
        if(temp==len2) {
            count++;
                    // printf("old_i = %d",i);
            i-=len2;
                    // printf(" new_i = %d\n",i);
        }
    }
    printf("%d\n",count);
    return 0;
}