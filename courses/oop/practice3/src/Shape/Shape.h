#ifndef SHAPE_H
#define SHAPE_H

class Shape {
    public:
        Shape();
        Shape(const Shape& oldShape);
        ~Shape();
        virtual const double calculateArea();
};

#endif
