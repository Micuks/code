#include <stdio.h>
#include <math.h>

int main() {
    int max(int a, int b);
    int a, b, c, d;
    scanf("%d%d%d", &a, &b, &c);
    if(a >= b && a >= c)
        d = max(a, b);
    else {
        if(b >= a && b >= c)
            d = max(a, b);
        else {
        d = max(a, b);
        }
    }
    printf("%d", d);
}
