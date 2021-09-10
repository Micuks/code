#include <cstdio>
const int maxn = 30;
const int inf = 1 << 22;
int sum, n, ans, x[maxn], g[maxn][maxn];

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}
int constraint(int t) {
    return sum < ans;
}
int min(int a, int b) {
    return a < b ? a : b;
}
void backtrack(int t) {
    if(t <= n) {
        for(int i = t; i <= n; i++) {
            swap(x[i], x[t]);
            if(t < n)
                sum += g[x[t]][x[t+1]];
            else if(t == n)
                sum += g[x[1]][x[n]];
            if(constraint(t)) {
                if(t >= n) {
                    ans = min(ans, sum);
                }
                else t++;
            }
            if(t < n)
                sum -= g[x[t]][x[t+1]];
            else if(t == n)
                sum -= g[x[1]][x[n]];
            swap(x[i], x[t]);
        }
    }
    else t--;
}
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
