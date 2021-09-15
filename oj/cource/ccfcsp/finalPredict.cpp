#include <algorithm>
#include <cstdio>

const int maxn = 1e5 + 10;

pair<int,int>a[maxn];
int p, ansz, m, n;

int cals(int dz, int uz) {
    int ans = 0;
    for(int i = 1; i <= m; i++) {
        if(a[i] >= uz)
            break;
        else if(a[i] >= dz) {
            if(rl[i] == 0)
                ans++;
            else ans--;
        }
    }
    //printf("ans = %d ", ans);
    return ans;
}

void dp() {
    ansz = p = 0;
    int msum = 0;
    for(int i = 1; i <= n; i++) {
        p += cals(b[i-1], b[i]);
        //printf("p = %d\n", p);
        if(p >= msum) {
            //printf("ansz = %d, b[i] = %d\n", ansz, b[i]);
            msum = p;
            ansz = b[i];
        }
    }
}

void swap(int& n1, int& n2) {
    int tmp = n1;
    n1 = n2;
    n2 = tmp;
}

int main() {
    scanf("%d", &m);
    for(int i = 1; i <= m; i++) {
        scanf("%d%d", a[i].first, a[i].second);
    }
    sort(a+1, m+1+a);

    n = 0;
    b[++n] = a[1];
    for(int i = 2; i <= m; i++) {
        if(a[i] != a[i-1])
            b[++n] = a[i];
    }

    //for(int i = 1; i <= n; i++) {
    //    printf("%d ", b[i]);
    //}
    //putchar('\n');
    dp();
    printf("%d\n", ansz);
    return 0;
}
