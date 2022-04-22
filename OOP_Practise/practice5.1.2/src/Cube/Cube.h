#ifndef CUBE_H
#define CUBE_H

#include "Rectangle.h"

class Cube : Rectangle {
    public:
        Cube();
        Cube(double length);
        Cube(const Cube& oldCube);
        ~Cube();
        const double calculateArea();
    private:
        double mLength;
};

#endif
