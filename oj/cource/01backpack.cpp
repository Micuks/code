#include <cstdio>
const int maxn = 4e5 + 10;
int m[maxn];
int w[maxn], v[maxn];
int max(int a, int b) {
    return a > b ? a : b;
}
void maxpack(int n, int c) {
    int i, j;
    for(i = 0; i <= c; i++) m[i] = 0;
    for(i = 1; i <= n; i++) {
        for(j = c; j >= 0; j--) {
            if(w[i] <= j)
                m[j] = max(m[j-w[i]] + v[i], m[j]);
        }
    }
}

int main() {
    int n, c;
    scanf("%d%d", &n, &c);
    for(int i = 1; i <= n; i++)
        scanf("%d%d", w+i, v+i);
    w[0] = v[0] = 0;
    maxpack(n, c);
    printf("%d\n", m[c]);
    return 0;
}
