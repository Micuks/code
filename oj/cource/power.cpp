#include<iostream>
using namespace std;
long long power(int bas, int pow) {
    long long ans = 1;
    while(pow) {
        if(pow % 2) {
            ans = 1ll * ans * bas;
        }
        bas *= bas;
        pow /= 2;
    }
    return ans;
}
int main() {
    int bas, pow;
    while(cin >> bas >> pow) 
        cout << power(bas, pow);
    return 0;
}
