#include <iostream>
#include <cmath>

class Point {
    public:
        Point(double x = -1, double y = -1);
        Point(const Point& rhs);
        ~Point();

        Point& operator=(const Point& rhs);
        void printPoint() const;

        friend const double calculateDistance(const Point& pointA, const Point& pointB);
    private:
        double mX;
        double mY;
};

const double calculateDistance(const Point& pointA, const Point& pointB);
