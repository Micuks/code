#include <iostream>
#include "Circle.h"

using namespace std;

int main() {
    Circle c1;
    Circle c2;
    c1 = Circle::createCircle();
    cout << "Created first circle:\n";
    c1.getCenter().printPoint();
    cout << endl << "radius = " << c1.getRadius() << endl;

    c2 = Circle::createCircle();
    c2.getCenter().printPoint();
    cout << endl << "radius = " << c2.getRadius() << endl;

    cout << "The distance between the center of two circles is " << calculateDistance(c1.getCenter(), c2.getCenter()) << endl;
    cout << "The sum of the radius of two circles is " << c1.getRadius() + c2.getRadius() << endl;

    if(intersectOrNot(c1, c2)) {
        cout << "The two circles are intersected.\n";
    } else {
        cout << "The two circles are not intersected.\n";
    }

    cout << endl;
    return 0;
}
