#include<cstdio>
const int maxn = 1e4 + 10;
int c[maxn][maxn];
int x[maxn], y[maxn];
int lcs(int* x, int* y, int m, int n) {
    int i, j;
    c[0][0] = 0;
    for(i = 1; i <= m; i++) c[i][0] = 0;
    for(j = 1; j <= n; j++) c[0][j] = 0;
    for(j = 1; j <= n; j++) {
        for(i = 1; i <= m; i++) {
            if(x[i] == y[j])
                c[i][j] = c[i-1][j-1] + 1;
            else if(c[i-1][j] >= c[i][j-1])
                c[i][j] = c[i-1][j];
            else
                c[i][j] = c[i][j-1];
        }
    }
    return c[m][n];
}
int main() {
    int n;
    scanf("%d", &n);
    for(int j = 1; j <= n; j++)
        scanf("%d", &x[j]);
    for(int j = 1; j <= n; j++)
        scanf("%d", &y[j]);
    printf("%d\n", lcs(x, y, n, n));
    return 0;
}
