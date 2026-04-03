#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
    public:
        Point();
        Point(int x, int y);
        Point(const Point& oldPoint);
        ~Point();

        Point& operator=(const Point& oldPoint);
        Point& operator++();
        Point& operator++(int);
        Point& operator--();
        Point& operator--(int);
        friend std::ostream& operator<<(std::ostream& oStr, const Point& point);

    private:
        int mX;
        int mY;
};

#endif
