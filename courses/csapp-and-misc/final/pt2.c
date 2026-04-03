#include<stdio.h>
#include<stdlib.h>
int main() {
    int n;
    scanf("%d",&n);
    char** a=(char**)malloc(n*sizeof(char*));
    for(int i=0;i<n;i++)
        a[i]=(char*)malloc(25*sizeof(char));
    for(int i=0;i<n;i++)
        scanf("%s",a[i]);
    int t,ord;
    scanf("%d",&t);
    for(int i=0;i<t;i++) {
        scanf("%d",&ord);
        printf("%s\n",a[ord-1]);
    }
    for(int i=0;i<n;i++) free(a[i]);
    free(a);
    return 0;
}