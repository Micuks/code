#pragma once

#include "ssdexport.h"
namespace SSD {

    struct SSDEXPORT SimPoint2D
    {
        //@brief constructor.
        SimPoint2D();

        //@brief constructor.
        //@param [_x, _y] is 2d point as input.
        SimPoint2D(double _x, double _y);

        //@brief destructor.
        ~SimPoint2D();

        //@brief normalize function.
        void Normalize();

        //@brief x value.
        double x;

        //@brief y value.
        double y;
    };
}