#include<iostream>
using namespace std;
void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}
void sort(int* arr, int len) {
    for(int i = 0; i < len; i++) {
        for(int j = len-1; j > i; j--) {
            if(arr[j] > arr[j-1])
                swap(arr[j-1], arr[j]);
        }
    }
}
int main() {
    int arr[] = {1, 2, 3, 4, 5, };
    int len = (int) sizeof(arr) / sizeof(*arr);
    sort(arr, len);
    for(int i = 0; i < len; i ++) 
        cout << arr[i] << ' ';
    cout << endl;
    return 0;
}
