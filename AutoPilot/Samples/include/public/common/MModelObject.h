#pragma once

#include "public/libexport.h"
#ifdef STATIC_SSD
#include "SSD/public/SimString.h"
#include "SSD/public/SimPoint3D.h"
#include "SSD/public/SimVector.h"
#else
#include "SSD/SimString.h"
#include "SSD/SimPoint3D.h"
#include "SSD/SimVector.h"
#endif
#include <cmath>

namespace HDMapStandalone {
    struct LIBEXPORT MModelObject
    {
        //@brief model object's id.
        long id;

        //@brief model object's location.
        SSD::SimPoint3D pt;

        //@brief heading normalized vector.
        SSD::SimPoint3D heading;

        //@brief model's type.
        SSD::SimString type;

        //@brief model's obj file path.
        SSD::SimString modelPath;
    };
}