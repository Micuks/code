#pragma once

#include "public/libexport.h"
#ifdef STATIC_SSD
#include "SSD/public/SimString.h"
#include "SSD/public/SimPoint3D.h"
#else
#include "SSD/SimString.h"
#include "SSD/SimPoint3D.h"
#endif

namespace HDMapStandalone {
    struct LIBEXPORT MAbstractRoadInfo
    {
        //@brief constructor.
        MAbstractRoadInfo();

        //@brief r-value copy constructor.
        MAbstractRoadInfo(MAbstractRoadInfo&& l) noexcept;

        //@brief copy constructor.
        MAbstractRoadInfo(const MAbstractRoadInfo& l) noexcept;

        //@brief assignment.
        MAbstractRoadInfo& operator= (const MAbstractRoadInfo& l);

        //@brief laneName, formatted as roadId_sectionIndex_laneId.
        //SSD::SimString laneName;
        long roadId;

        //@brief sample point list of center line.
        SSD::SimPoint3DVector centerLine;
    };
}