#include<iostream>

using namespace std;

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

long long binpow(int bas, int pow) {
    long long ans = 1;
    while(pow) {
        if(pow&1)
            ans *= bas;
        bas *= bas;
        pow >>= 1;
    }
    return ans;
}

int caldep(int a) {
    int ans = 0;
    while(binpow(2, ans) < a)
        ans++;
    return ans;
}

void sort_unit(int* arr, int begin, int end) {
    int dad = begin;
    int son = 2 * dad + 1;
    while(son <= end) {
        if(arr[son] < arr[son+1] && son < end)
            son++;
        if(arr[dad] >= arr[son])
            return;
        else {
            swap(arr[dad], arr[son]);
            dad = son;
            son = 2 * son + 1;
        }
    }
}

void heap_sort(int* arr, int len) {
    for(int i = len/2 - 1; i >= 0; i--) {
        sort_unit(arr, i, len-1);
    }
    for(int i = len-1; i > 0; i--) {
        swap(arr[0], arr[i]);
        sort_unit(arr, 0, i-1);
    }
}

int main() {
    int arr[] = { 3, 5, 3, 0, 8, 6, 1, 5, 8, 6, 2, 4, 9, 4, 7, 0, 1, 8, 9, 7, 3, 1, 2, 5, 9, 7, 4, 0, 2, 6 };
    int len = (int) sizeof(arr) / sizeof(*arr);
    heap_sort(arr, len);
    for (int i = 0; i < len; i++)
        cout << arr[i] << ' ';
    cout << endl;
    return 0;
}
