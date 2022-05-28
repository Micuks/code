#include "Point.h"
#include <iostream>

using namespace std;

int main() {
    int x, y;
    cout << "Enter the x and y coordinate of the point.\n";
    cin >> x >> y;
    Point p(x, y);
    cout << "p = ";
    cout << p << endl;
    cout << "p++ = ";
    cout << p++ << endl;
    cout << "p-- = ";
    cout << p-- << endl;
    cout << "++p = ";
    cout << ++p << endl;
    cout << "--p = ";
    cout << --p << endl;

    return 0;
}
