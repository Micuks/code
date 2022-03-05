#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 20;
int cnt = 0, n, x[maxn];
int r[maxn], c[maxn], l1[maxn], l2[maxn];
void output() {
    if(cnt++ < 3) {
        for(int k = 1; k <= n; k++)
            printf(&" %d" [!(k-1)], x[k]);
        putchar('\n');
    }
}

void backtrack(int t) {
    if(t > n)
        output();
    else  {
        for(int i = 1; i <= n; i++) {
            if(!(c[i] || l1[n+t-i] || l2[i+t])) {
                x[t] = i; c[i] = 1; l1[n+t-i] = 1; l2[i+t] = 1;
                backtrack(t+1);
                c[i] = 0; l1[n+t-i] = 0; l2[i+t] = 0;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    backtrack(1);
    printf("%d\n", cnt);
    return 0;
}
