#include <cstdio>

const int maxn = 1e5 + 10;
void getmax(int* a, int n, int& f, int& r, int& maxsum) {
    maxsum = -1001;
    int max = 0, tmp;
    for(int i = n - 1; i >= 0; i--) {
        if(max > 0) {
            max += a[i];
        }
        else {
            max = a[i];
            tmp = i;
        }
        if(maxsum <= max) {
        maxsum = max;
        f = i;
        r = tmp;
        }
    }
}

int main() {
    int n, kases;
    int num[maxn];
    scanf("%d", &kases);
    for(int k = 1; k <= kases; k++) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%d", num + i);
        }
        int f, r, maxsum;
        getmax(num, n, f, r, maxsum);
        printf(&"\nCase %d:\n" [ !(k-1)], k);
        printf("%d %d %d\n", maxsum, f + 1, r + 1);
    }
    return 0;
}
