#include <iostream>

using namespace std;

void __print(char a) { cout << a; }
void __print(int a) { cout << a; }
void __print(double a) { cout << a; }
void __print(const char *a) { cout << a; }
void __print(const string &a) { cout << a; }
template <typename T, typename V> void __print(const pair<T, V> &a) {
    cout << '{';
    _print(a.first);
    cout << ", ";
    _print(a.second);
    cout << '}';
}
template <typename T> void __print(const T &a) {
    int t = 0;
    cout << '{';
    for (auto &item : a) {
        cout << (t++ ? ", " : "");
        __print(item);
    }
    cout << '}';
}

void _print() { cout << "]\n"; }

template <typename T, typename... V> void _print(T x, V... y) {
    __print(x);
    if (sizeof...(y))
        cout << ", ";
    _print(y...);
}

#define deb(x...)                                                              \
    cout << #x << "=[";                                                        \
    _print(x)
