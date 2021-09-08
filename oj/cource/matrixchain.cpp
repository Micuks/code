#include <cstdio>
const int maxn = 210;
int p[maxn], m[maxn][maxn];
void minMatrixChain(int n) {
    int i, j;
    for(i = 1; i <= n; i++)
        m[i][i] = 0;
    for(int l = 2; l <= n; l++) {
        for(i = 1; i <= n - l + 1; i++) {
            j = l + i - 1;
            m[i][j] = m[i][i] + m[i+1][j] + p[i-1] * p[i] * p[j];
            for(int k = i + 1; k < j; k++) {
                int tmp = m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j];
                m[i][j] = tmp < m[i][j] ? tmp : m[i][j];
            }
        }
    }
}

int main() {
    int n;
    while(scanf("%d", &n) == 1) {
        for(int i = 0; i <= n; i++)
            scanf("%d", p + i);
        minMatrixChain(n);
        printf("%d\n", m[1][n]);
    }
    return 0;
}
