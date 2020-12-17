#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void change(char *a,char *b,int alen,int blen){
    char temp;
    int len=(alen>blen)?alen:blen;
    for(int i=0;i<len;i++) {
        temp=a[i];
        a[i]=b[i];
        b[i]=temp;
    }
}
void ShellSort(char **a,int len) {
    for(int gap=len/2;gap>=1;gap/=2) {
        for(int i=0;i<gap;i++) {
            for(int k=i;k+gap<len;k+=gap) {
                int j;
                for(j=k;j+gap<len;j+=gap)
                    ;
                j-=gap;
                for(;j>=0;j-=gap) {
// printf("\tj = %d",j);
                    if(strcmp(a[j],a[j+gap])>0)
                        change(a[j],a[j+gap],strlen(a[j]),strlen(a[j+gap]));
                }
            }
        }
// printf("\n");
    }
}
int main() {
    int n;
    scanf("%d",&n);
    getchar();
    char **matrix=(char**)malloc(sizeof(char *)*n);
    for(int i=0;i<n;i++) 
        matrix[i]=(char*)malloc(sizeof(char)*105);
    for(int i=0;i<n;i++) {
        char temp;
        for(int j=0;(temp=getchar())!='\n'&&temp!=EOF;j++) {
            matrix[i][j]=temp;
            matrix[i][j+1]='\0';
        }
    }
    // for(int i=0;i<n;i++)
    //     printf("%s\n",matrix[i]);
    ShellSort(matrix,n);
    // printf("answer:\n");
    for(int i=0;i<n;i++)
        printf("%s\n",matrix[i]);
    return 0;
}