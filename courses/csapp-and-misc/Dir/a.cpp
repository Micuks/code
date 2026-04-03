#include <cstdio>
int main() {
    double n, x, y;
    scanf("%lf%lf%lf", &n, &x, &y);
    printf("%lf", n/x * (y - x));
    return 0;
}
