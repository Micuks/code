#include <iostream>

using namespace std;

const int maxn = 1e5 + 100;

int a[maxn], t[maxn];
void mergesort(int pl, int pr) {
    if(pr - pl <= 1)
        return;
    int pm = (pl + pr) / 2;
    mergesort(pl, pm);
    mergesort(pm, pr);
    int p = pl, q = pm, s = pl;
    while(s < pr) {
        if((a[p] <= a[q] && p < pm) || q >= pr) {
            t[s] = a[p];
            p++;
        }
        else {
            t[s] = a[q];
            q++;
        }
        s++;
    }
    for(int i = pl; i < pr; i++)
        a[i] = t[i];
}

int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> a[i];
    mergesort(0, n);
    for(int i = 0; i < n; i++)
        cout << a[i] << ' ';
    cout << endl;
    return 0;
}
