#include <cstdio>

const int maxn = 1e5 + 10;

void process(int* num, int len, int& anssum, int& ansid, int& anscnt) {
    int sum = 0, cnt = 0;
    for(int i = len - 1; i >= 0; i--) {
        if(sum > 0) {
            sum += num[i];
            cnt++;
        }
        else {
            sum = num[i];
            cnt = 1;
        }
        if(anssum <= sum) {
            ansid = i;
            anssum = sum;
            anscnt = cnt;
        }
    }
}

int main() {
    int n, kases;
    int num[maxn];
    scanf("%d", &kases);
    for(int k = 1; k <= kases; k++) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%d", num + i);
        }
        int anssum = 0, ansid = 0, anscnt = 0;
        process(num, n, anssum, ansid, anscnt);
        printf(&"\nCase %d:\n" [ !(k-1)], k);
        printf("%d %d %d\n", anssum, ansid + 1, ansid + anscnt);
    }
    return 0;
}
