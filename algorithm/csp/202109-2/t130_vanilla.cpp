#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 500010, M = 10010;

int n;
int a[N], cnt[M];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    n = unique(a + 1, a + n + 1) - a - 1;
    a[0] = a[n + 1] = 0;

    for (int i = 1; i <= n; i++) {
        int x = a[i - 1], y = a[i], z = a[i + 1];
        if (x < y && z < y)
            cnt[y]++;
        else if (x > y && z > y)
            cnt[y]--;
    }

    int res = 0, sum = 0;
    for (int i = M - 1; i; i--) {
        sum += cnt[i];
        res = max(res, sum);
    }

    printf("%d\n", res);
    return 0;
}
