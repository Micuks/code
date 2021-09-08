#include <cstdio>

const int maxn = 1e5 + 10;

void getmax(int* a, int n, int& f, int& r, int& maxsum) {
    int c[n+1], d[n+1];

    c[n-1] = a[n-1];
    d[n-1] = n - 1;
    for(int i = n - 2; i >= 0; i--) {
        if(c[i+1] > 0) {
            c[i] = c[i+1] + a[i];
            d[i] = d[i+1];
        }
        else {
            c[i] = a[i];
            d[i] = i;
        }
        if(maxsum <= c[i]) {
        maxsum = c[i];
        f = i;
        }
    }
    //for(int i = n-1; i >= 0; i--) {
        //if(c[i] >= maxsum) {
            //maxsum = c[i];
            //f = i;
            //r = d[i];
        //}
    //}
    r = d[f];
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
        int f, r, maxsum = 0;
        getmax(num, n, f, r, maxsum);
        printf(&"\nCase %d:\n" [ !(k-1)], k);
        printf("%d %d %d\n", maxsum, f, r);
    }
    return 0;
}
