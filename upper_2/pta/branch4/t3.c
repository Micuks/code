#include <stdio.h>

int getString(char *source, char *strPtr[]);

int main()
{
    char str[100005];
    char *strPtr[1005] = {0};
    int i, num;
    // gets(str);
    num = getString(str, strPtr);
    for (i = 0; i < num; i++)
        puts(strPtr[i]);

    return 0;
}
int getString(char* source,char* strPtr[]) {
    int ptr=-1;
    int count=0,flag=0;
    while(*(source+(++ptr))!='\0') {
        if(flag==0&&((*(source+ptr)>='A'&&*(source+ptr)<='Z')||(*(source+ptr)<='z'&&*(source+ptr)>='a'))) {
            flag=1;
            *(strPtr+(count++))=source+ptr;
        }
        else if(flag==1&&(*(source+ptr)==' ')) {
            flag=0;
            *(source+ptr)='\0';
        }
    }
    // printf("count = %d\n",count);
    return count;
}