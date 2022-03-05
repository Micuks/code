#include <complex>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;
const int maxn = 10000010;
const double eps = 1e-6;
complex<double> f[maxn], g[maxn];

int makeitvalid(int n) {
    int res = 1;
    while(res < n)
        res <<= 1;
    return res;
}

void fft(complex<double>* a, int n, int rev) {
    if(n == 1) {
        return;
    }
    complex<double> aodd[n/2 + 1], aeven[n/2 + 1];
    for(int i = 0; i < n; i++) {
        if(i % 2 == 1) {
            aodd[i/2] = a[i];
        }
        else {
            aeven[i/2] = a[i];
        }
    }
    fft(aodd, n/2, rev);
    fft(aeven, n/2, rev);
    complex<double> w1(cos(2 * M_PI / n), rev * sin(2 * M_PI / n)), wk(1, 0);
    for(int i = 0; i < n/2; i++) {
        a[i] = aeven[i] + wk * aodd[i];
        a[i + n/2] = aeven[i] - wk * aodd[i];
        wk *= w1;
    }
}

int main() {
    int m, n;
    scanf("%d%d", &m, &n);
    for(int i = 0; i <= m; i++) {
        double tmp;
        scanf("%lf", &tmp);
        f[i].real(tmp);
    }
    for(int  i = 0; i <= n; i++) {
        double tmp;
        scanf("%lf", &tmp);
        g[i].real(tmp);
    }
    int mn = makeitvalid(m + n);
    fft(f, mn, 1);
    fft(g, mn, 1);
    for(int i = 0; i < mn; i++)
        f[i] = f[i] * g[i];
    fft(f, mn, -1);
    for(int i = 0; i < m + n + 1; i++)
        printf("%.0f ", f[i].real() / mn + eps);
    putchar('\n');
    return 0;
}
