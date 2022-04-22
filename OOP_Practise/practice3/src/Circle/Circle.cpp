#include <iostream>
#include "Circle.h"

using namespace std;

Circle::Circle() {
    cout << "Circle::Circle() is called.\n";
    mRadius = 0.0;
}

Circle::Circle(double r) {
    cout << "Circle::Circle(double x, double y, double r) is called\n";
    mRadius = r;
}

Circle::~Circle() {
    cout << "Circle::~Circle() is called\n";
}

const double Circle::calculateArea() {
    return M_PI * mRadius * mRadius;
}
