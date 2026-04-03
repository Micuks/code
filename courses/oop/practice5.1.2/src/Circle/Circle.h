#include "Shape.h"

const double M_PI = 3.1415926535897932384626;

class Circle : Shape {
    public:
        Circle();
        Circle(double r);
        ~Circle();
        const double calculateArea();
    private:
        double mRadius;
};
