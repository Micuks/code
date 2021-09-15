
#include <cstdio>

const int maxn = 900;
int s, n, l, r, t, cnt;
int psum[maxn][maxn], a[maxn][maxn];

int max(int n1, int n2) {
    return n1 > n2 ? n1 : n2;
}

int min(int n1, int n2) {
    return n1 < n2?n1 : n2;
}

void process() {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            int l2 = max(1, j - r);
            int r2 = min(n, j + r);
            int u = max(1, i - r);
            int d = min(n, i + r);
            int t2 = psum[d][r2] - psum[u-1][r2] - psum[d][l2-1] + psum[u-1][l2-1];
            if(t2 <= 0)
                cnt++;
        }
    }
}

int main() {
    scanf("%d%d%d%d", &n, &l, &r, &t);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            scanf("%d", &a[i][j]);
            a[i][j] -= t;
            psum[i][j] = psum[i][j-1] + psum[i-1][j] - psum[i-1][j-1] + a[i][j];
        }
    }
    process();
    printf("%d\n", cnt);
    return 0;
}
