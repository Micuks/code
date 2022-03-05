#include<cstdio>
const int maxn = 1e5 + 10;
int c[2][maxn];
int x[maxn], y[maxn];
int lcs(int m, int n) {
    int i, j;
    for(i = 0; i <= n; i++) c[0][i] = 0;
    for(i = 0; i <= n; i++) c[1][i] = 0;
    int rev = 1;
    for(i = 1; i <= m; i++) {
        for(j = 1; j <= n; j++) {
            if(x[i] == y[j])
                c[rev][j] = c[!rev][j-1] + 1;
            else if(c[rev][j-1] > c[!rev][j])
                c[rev][j] = c[rev][j-1];
            else
                c[rev][j] = c[!rev][j];

        }
        rev = !rev;
    }
    return c[!rev][n];
}
void print(int m) {
    for(int k = 0; k <= 1; k++) {
        for(int l = 0; l <= m; l++)
            printf("%d ", c[k][l]);
        putchar('\n');
    }
}
int main() {
    int n;
    scanf("%d", &n);
    for(int j = 1; j <= n; j++)
        scanf("%d", &x[j]);
    for(int j = 1; j <= n; j++)
        scanf("%d", &y[j]);
    printf("%d\n", lcs(n, n));
    return 0;
}
