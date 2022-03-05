#include <stdio.h>
int main() {
    char c1 = 13, c2 = 8;
    int a;
    scanf("%d", &a);
    printf("a = %d\n", a);
    for(int i = 0; i < 5; i++)
        printf("%c", c1);
    printf("%c", c2);
    return 0;
}
