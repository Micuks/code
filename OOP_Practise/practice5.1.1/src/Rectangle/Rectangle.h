#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>
#include "Shape.h"

class Rectangle : Shape {
    public:
        Rectangle();
        Rectangle(double length, double width);
        Rectangle(const Rectangle& oldRectangle);
        ~Rectangle();
        const double calculateArea();
    private:
        double mLength;
        double mWidth;
};

#endif
