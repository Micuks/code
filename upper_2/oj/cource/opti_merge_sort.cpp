#include <iostream>

using namespace std;

const int maxn = 1e5 + 100;

void mergesort(int* a, int len) {
    int flag = 1;
    int b[len + 10];
    for(int s = 2; s < len; s += s) {
        for(int i = 0; i < len; i += s) {
            int p1 = i, p2 = i + s/2, p3 = i;
            while(p2 <= len && p3 < len && p1 <= i + s/2 && p2 <= i + s) {
                if((p2 == len || p2 == i + s) && p1 < i + s/2) {
                    if(flag)
                        b[p3] = a[p1++];
                    else 
                        a[p3] = b[p1++];
                }
                else if(p1 == i + s/2 && p1 < len && p2 < i + s) {
                    if(flag)
                        b[p3] = a[p2++];
                    else 
                        a[p3] = b[p2++];
                }
                else if(flag && p2 != len && p2 != i + s && p1 != i + s/2) {
                    if(a[p1] <= a[p2]) {
                        b[p3] = a[p1++];
                    }
                    else {
                        b[p3] = a[p2++];
                    }
                }
                else {
                    if(b[p1] <= b[p2]) {
                        a[p3] = b[p1++];
                    }
                    else {
                        a[p3] = b[p2++];
                    }
                }
                p3++;
            }
            for(int k = 0; k < len; k++) {
                printf("%d ", a[k]);
            }
            putchar('\n');
            for(int k = 0; k < len; k++) {
                printf("%d ", b[k]);
            }
            putchar('\n');
        }
        flag = !flag;
    }
}

int main() {
    int n;
    int a[maxn];
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> a[i];
    mergesort(a,n);
    for(int i = 0; i < n; i++)
        cout << a[i] << ' ';
    cout << endl;
    return 0;
}
