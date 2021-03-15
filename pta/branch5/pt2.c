#include<stdio.h>
#include<string.h>
#include<malloc.h>
int main() {
    int n;
    char temp[1000];
    scanf("%d",&n);
    char** chptr=(char**)malloc(n*sizeof(char*));
    char ch;
    int ptr;
    getchar();
    for(int i=0;i<n;i++) {
        ptr=0;
        while((ch=getchar())!='\n'&&ch!=EOF)
            temp[ptr++]=ch;
        temp[ptr++]='\0';
        chptr[i]=(char*)malloc(ptr*sizeof(char));
        for(int j=0;j<ptr;j++)
            chptr[i][j]=temp[j];
    }
    //     for(int i=0;i<n;i++) {
    //     printf("%s\n",chptr[i]);
    // }
    for(int i=0;i<n;i++) {
        // printf("i = %d, ",i);
        for(int j=n-1;j>i;j--) {
            // printf("j = %d\n",j);
            if(strcmp(chptr[j],chptr[j-1])<0) {
                char* p=chptr[j];
                chptr[j]=chptr[j-1];
                chptr[j-1]=p;
            }
        }
    }
    for(int i=0;i<n;i++) {
        printf("%s\n",chptr[i]);
        // free(chptr[i]);
    }
    // free(chptr);
    return 0;
}