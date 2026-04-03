#include<iostream>
#include<string>
#include<sstream>
using namespace std;
const int maxn = 100010;
int binarysearch(int* arr,int pl, int pr, int tar) {
    //arr is arranged from small to big.
    int pm = (pl + pr) /2;
    while(pl <= pr) {
        if(arr[pm] == tar) {
            return pm;
        }
        else if(arr[pm] < tar) {
            pl = pm + 1;
        }
        else {
            pr = pm - 1;
        }
            pm = (pl + pr) / 2;
    }
    return -1;
}
int main() {
    int arr[maxn];
    int pl, pr, tar;
    string str;
    while(getline(cin, str)) {
        stringstream ss(str);
        int num, cnt = 0;
        while(ss >> num) {
            arr[cnt++] = num;
        }
        cin >> pl >> pr >> tar;
        cout << binarysearch(arr, pl, pr, tar) << endl;
    }
    return 0;
}
