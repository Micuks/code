#include<iostream>

using namespace std;

const int maxn = 200010;

void process(int* num, int len, int& anssum, int& ansid, int& anscnt) {
    int sum = anssum, cnt = anscnt;
    //cout << "num[i]\tsum\tcnt\n";
    //cout << *num << '\t'<< sum <<'\t'<< cnt << endl;
    for(int i = 1; i < len; i++) {
        if(sum > 0) {
            sum += num[i];
            cnt++;
        }
        else {
            sum = num[i];
            cnt = 1;
        }
        //cout << num[i] << '\t'<< sum <<'\t'<< cnt << endl;
        if(anssum < sum) {
            ansid = i;
            anssum = sum;
            anscnt = cnt;
        }
    }
}

int main() {
    int n;
    int num[maxn];
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> num[i];
        //cout << num[i] << ' ';
    }
    //cout << endl;
    int anssum = *num, ansid = 0, anscnt = 1;
    process(num, n, anssum, ansid, anscnt);
    cout << anssum << endl;
    return 0;
}
