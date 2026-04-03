#include <cstdio>

int main() {
    int d, n, kases;
    scanf("%d", &kases);
    while(scanf("%d%d", &d, &n) == 2) {
        int ptr = 1;
        while(ptr < 1<<(d-1)) {
            if(n%2) {
                n = (n+1) / 2;
                ptr *= 2;
            }
            else {
                n /= 2;
                ptr = ptr*2 + 1;
            }
        }
        printf("%d\n", ptr);
    }
    return 0;
}
