#include "Point.h"

class Circle {
    public:
        Circle();
        Circle(const Circle &oldCircle);
        Circle(Point center, double radius);
        Circle(double x, double y, double radius);
        ~Circle();

        friend const bool intersectOrNot(const Circle &circleA,
                const Circle &circleB);
        static Circle createCircle();
        const Point& getCenter() const;
        const double& getRadius() const;

    private:
        Point mCenter;
        double mRadius;
};

const bool intersectOrNot(const Circle &circleA,
        const Circle &circleB);
