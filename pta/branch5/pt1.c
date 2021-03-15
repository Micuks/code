#include<stdio.h>
#include<string.h>
int main() {
    int n;
    scanf("%d",&n);
    int ptr=0;
    char ch;
    char str[100105];
    char* chptr[105];
    getchar();
    for(int i=0;i<n;i++) {
        chptr[i]=str+ptr;
        while((ch=getchar())!='\n'&&ch!=EOF) str[ptr++]=ch;
        str[ptr++]='\0';
    }
    // for(int i=0;i<n;i++) {
    //     printf("%s\n",chptr[i]);
    // }
    for(int i=0;i<n;i++) {
        for(int j=n-1;j>i;j--) {
            if(strcmp(chptr[j],chptr[j-1])<0) {
                char* temp=chptr[j];
                chptr[j]=chptr[j-1];
                chptr[j-1]=temp;
            }
        }
    }
    for(int i=0;i<n;i++) {
        printf("%s\n",chptr[i]);
    }
    return 0;
}