#include "Circle.h"
#include <iostream>

using namespace std;

Circle::Circle() : mCenter() {
    cout << "Circle::Circle() is called.\n";
    mRadius = 0;
}

Circle::Circle(const Circle &oldCircle) {
    cout << "Circle::Circle(const Circle& oldCircle) is called.\n";
    mCenter = oldCircle.mCenter;
    mRadius = oldCircle.mRadius;
}

Circle::Circle(Point center, double radius) : mCenter(center), mRadius(radius) {
    cout << "Circle::Circle(Point center, double radius) is called.\n";
}

Circle::Circle(double x, double y, double radius) : mCenter(x, y) {
    cout << "Circle::Circle(double x, double y, double radius) is called\n";
    mRadius = radius;
}

Circle::~Circle() {
    cout << "Circle::~Circle() is called.\n";
}

const Point& Circle::getCenter() const {
    return mCenter;
}

const double& Circle::getRadius() const {
    return mRadius;
}

const bool intersectOrNot(const Circle &circleA, const Circle &circleB) {
    if(calculateDistance(circleA.getCenter(), circleB.getCenter()) < circleA.getRadius() + circleB.getRadius()) {
        return true;
    } else {
        return false;
    }
}

Circle Circle::createCircle() {
    cout << "Enter the coordinates of the center of the circle.\n";
    double x, y;
    cin >> x >> y;
    Point center(x, y);

    cout << "Enter the radius of the circle at";
    center.printPoint();
    cout << "\n";

    double radius = 0;
    cin >> radius;
    Circle c = Circle(center, radius);
    return c;
}
