#include <bitset>
#include <iostream>

using namespace std;

int main() {
    bitset<2000> a[2000];
    a[0].set(0);
    a[1].set(1);
    cout << a[0].test(0) << ' ' << a[1].test(1) << endl;
    a[2] = a[0] & a[1];
    a[3] = a[0] | a[1];
    cout << a[2].test(0) << ' ' << a[2].test(1) << endl;
    cout << a[3].test(0) << ' ' << a[3].test(1) << endl;

    return 0;
}
