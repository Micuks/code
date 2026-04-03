#include "Point.h"

using namespace std;

Point::Point(double x, double y) {
    cout << "Point::Point(double x, double y) is called\n";
    this->mX = x;
    this->mY = y;
}

Point::Point(const Point& rhs) {
    cout << "Point::Point(const Point& rhs) is called.\n";
    this->mX = rhs.mX;
    this->mY = rhs.mY;
}

Point::~Point() {
    cout << "Point::~Point() is called.\n";
}

Point& Point::operator=(const Point& rhs) {
    cout << "Point& Point::operator=(const Point& rhs)\n";
    if(this == &rhs) {
        cout << "Right value is equal to left value.\n";
        return *this;
    }

    this->mX = rhs.mX;
    this->mY = rhs.mY;
    return *this;
}

void Point::printPoint() const {
    cout << "(" << this->mX << ", " << this->mY << ")";
}

const double calculateDistance(const Point& pointA, const Point& pointB) {
    double distance = (pointA.mX - pointB.mX) * (pointA.mX - pointB.mX) + (pointA.mY - pointB.mY) + (pointA.mY - pointB.mY);
    distance = sqrt(distance);
    return distance;
}
