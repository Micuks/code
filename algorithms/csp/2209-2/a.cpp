#include <cstring>
#include <iostream>
#include <limits>

using namespace std;

// #define debug

#ifdef debug
#include "debug.hpp"
#else
#define deb(x...)
#endif

typedef long long ll;
int n, x;
const int N = 31;
const int MAXN = (int)3e5 + 1000;
ll a[N][MAXN];
int v[N];
ll sa; // sum value of all books

int main() {
    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        sa += v[i];
    }

    deb(sa);
    // Initialize dp
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= sa; j++) {
            a[i][j] = 0;
        }
    }

    // Do dp
    for (int i = 1; i <= n; i++) {
        deb(i, v[i]);
        for (ll j = sa; j >= v[i]; j--) {
            deb(a[i - 1][j], a[i - 1][j - v[i]] + v[i]);
            a[i][j] = max(a[i - 1][j], a[i - 1][j - v[i]] + v[i]);
            deb(i, j, a[i][j]);
        }
    }

    // Print result
    for (ll i = x; i <= sa; i++)
        if (a[n][i] >= x) {
            cout << a[n][i] << endl;
            return 0;
        }

    return 0;
}
