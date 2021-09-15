#include <iostream>

using namespace std;

const int maxn = 1e5+10;
int arr[maxn];

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void qsort(int l, int r) {
    if(l >= r)
        return;
    int i = l, j = r;
    while(i < j) {
        while(arr[j] >= arr[l] && i < j)
            j--;
        while(arr[i] <= arr[l] && i < j)
            i++;
        swap(arr[i], (i == j) ? arr[l] : arr[j]);
    }
    qsort(l, i-1);
    qsort(j+1, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> arr[i];
    qsort(1, n);
    for(int i = 1; i <= n; i++)
        cout << arr[i] << ' ';
    cout << endl;
}
