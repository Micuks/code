#include "Cube.h"

Cube::Cube() {
    std::cout << "Cube::Cube() is called.\n";
    mLength = 0;
}

Cube::Cube(double length) {
    std::cout << "Cube::Cube(double length) is called.\n";
    mLength = length;
}

Cube::~Cube() {
    std::cout << "Cube::~Cube() is called\n";
}

const double Cube::calculateArea() {
    return mLength * mLength;
}
