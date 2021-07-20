#pragma once

#include "ssdexport.h"
#include "SimVector.h"

namespace SSD {

    struct SSDEXPORT SimPoint3D
    {
        //@brief constructor.
        SimPoint3D();

        //@brief constructor.
        //@param [_x, _y, _z] is 3d point as input.
        SimPoint3D(double _x, double _y, double _z);

        //@brief destructor.
        ~SimPoint3D();

        //@brief normalize function.
        void Normalize();

        //@brief x value.
        double x;

        //@brief y value.
        double y;

        //@brief z value.
        double z;
    };

    template class SSDEXPORT SimVector<SimPoint3D>;
    typedef SimVector<SimPoint3D> SimPoint3DVector;
}
