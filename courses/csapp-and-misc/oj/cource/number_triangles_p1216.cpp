#include <cstdio>
#include <cstring>

const int maxn = 1010;
//可以改为由下到上状态转移， 把b[i][j]优化为一维数组
int findmax(int** a, int n) {
    int b[n+10][n+10];
    for(int i = 1; i <= n; i++)
        memset(b[i], 0, sizeof(b[i]));
    b[1][1] = **a;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i; j++) {
                b[i][j] = max(b[i-1][j-1], b[i-1][j]) + a[i][j];
            }
    }
    int ans = a[n][1];
    for(int i = 1; i <=n; i++)
        if(ans < a[n][i])
            ans = a[n][i];
    return ans;
}

int main() {
    int n, a[maxn][maxn];
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= i; j++)
            scanf("%d", &a[i][j]);
    printf("%d\n", findmax(a, n));
    return 0;
}
