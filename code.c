#include<stdio.h>
#include <stdarg.h>
void print(const char * format, ...) {
    va_list(args);
    va_start(args, format);
    printf(format, args);
    va_end(args);
}
int main() {
    int a = 10;
    char c = 'c';
    printf("%d a %c\n", a, c);
    print("%d a %c\n", a, c);
    return 0;
}
