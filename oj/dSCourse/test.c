#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    char a[100] = {"1x2+2x1+1x0"};
    printf("%s\n", a);
    int n;
    for(int i = 0; i < strlen(a); i++) {
        if(i == 0) {
            sscanf(a, "%d", &n);
            printf("%d ", n);
            getchar();
        }
        if(a[i] == 'x' || a[i] == '+') {
            sscanf(a+i+1, "%d", &n);
            printf("%d ", n);
            getchar();
        }
    }
    putchar('\n');
    return 0;
}
