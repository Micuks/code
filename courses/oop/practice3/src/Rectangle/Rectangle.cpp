#include "Rectangle.h"

Rectangle::Rectangle() : Shape() {
    std::cout << "Rectangle::Rectangle() is called\n";
    mLength = mWidth = 0.0;
}

Rectangle::Rectangle(double length, double width) : Shape() {
    std::cout << "Rectangle::Rectangle(double length, double width) is called\n";
    mLength = length;
    mWidth = width;
}

Rectangle::~Rectangle() {
    std::cout << "Rectangle::~Rectangle() is called.\n";
}

const double Rectangle::calculateArea() {
    return mLength * mWidth;
}
