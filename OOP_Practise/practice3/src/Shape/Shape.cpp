#include <iostream>
#include "Shape.h"

Shape::Shape() {
    std::cout << "Shape::Shape() is called.\n";
}

Shape::Shape(const Shape& oldShape) {
    std::cout << "Shape::Shape(const Shape& oldShape) is called.\n";
}

Shape::~Shape() {
    std::cout << "Shape::~Shape() is called.\n";
}

const double Shape::calculateArea() {
    std::cout << "const double Shape::calculateArea() is called.\n";
    return 0.0;
}
