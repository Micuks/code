#include <cstdio>
const int maxn = 30;
const int inf = 1 << 22;
int sum, n, ans, x[maxn], g[maxn][maxn];

int constraint(int t) {
    return sum < ans;
}
int min(int a, int b) {
    return a < b ? a : b;
}
void backtrack(int t) ;
int main() {
    int kases;
    scanf("%d", &kases);
    while(kases--) {
        ans = inf;
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            x[i] = i;
            for(int j = 1; j <= n; j++)
                scanf("%d", &g[i][j]);
        }
        sum = 0;
        backtrack(1);
        printf("%d\n", ans);
    }
    return 0;
}
