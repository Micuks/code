#include "Point.h"

using namespace std;

Point::Point() {
    cout << "Point::Point() is called.\n";
}

Point::Point(int x, int y) {
    mX = x;
    mY = y;
    cout << "Point::Point(int x, int y) is called.\n";
}

Point::Point(const Point& oldPoint) {
    mX = oldPoint.mX;
    mY = oldPoint.mY;
    cout << "Point::Point(const Point& oldPoint) is called.\n";
}

Point::~Point() {
    cout << "Point::~Point() is called.\n";
}

Point& Point::operator=(const Point& oldPoint) {
    mX = oldPoint.mX;
    mY = oldPoint.mY;
    return *this;
}

Point& Point::operator++() {
    ++mX;
    ++mY;
    return *this;
}

Point& Point::operator++(int) {
    mX++;
    mY++;
    return *this;
}

Point& Point::operator--() {
    mX--;
    mY--;
    return *this;
}

Point& Point::operator--(int) {
    mX--;
    mY--;
    return *this;
}

ostream& operator<<(ostream& oStr, const Point& point) {
    oStr << "(" << point.mX << ", " << point.mY << ")";
    return oStr;
}
