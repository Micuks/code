#pragma once

#include "public/libexport.h"
#ifdef STATIC_SSD
#include "SSD/public/SimString.h"
#include "SSD/public/SimPoint3D.h"
#else
#include "SSD/SimString.h"
#include "SSD/SimPoint3D.h"
#endif
#include "public/common/MRoadMark.h"

namespace HDMapStandalone {
    struct LIBEXPORT MLaneInfo
    {
        //@brief constructor.
        MLaneInfo();

        //@brief destructor.
        ~MLaneInfo();

        //@brief r-value copy constructor.
        MLaneInfo(MLaneInfo&& l) noexcept;

        //@brief copy constructor.
        MLaneInfo(const MLaneInfo& l) noexcept;

        //@brief assignment.
        MLaneInfo& operator= (const MLaneInfo& l);

        //@brief laneName, formatted as roadId_sectionIndex_laneId.
        SSD::SimString laneName;

        //@brief sample point list of left boundary.
        SSD::SimPoint3DVector leftBoundary;

        //@brief sample point list of right boundary.
        SSD::SimPoint3DVector rightBoundary;

        //@brief sample point list of center line.
        SSD::SimPoint3DVector centerLine;
    };

	struct LIBEXPORT MLaneLine
	{
		//@brief road mark list.
		SSD::SimVector<MRoadMark> roadmarkList;

		//@brief segment list each is a knot list of one segment. Its size is aligned with road mark list.
		SSD::SimVector<SSD::SimPoint3DVector> segmentList;
	};

	struct LIBEXPORT MLaneLineInfo
	{
		//@brief laneName, formatted as roadId_sectionIndex_laneId.
		SSD::SimString laneName;

		//@brief left boundary's MLaneLine
		MLaneLine leftBoundary;

		//@brief right boundary's MLaneLine
		MLaneLine rightBoundary;
	};
}