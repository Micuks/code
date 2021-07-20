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
#include "MLaneId.h"

namespace HDMapStandalone {

    struct LIBEXPORT MSegmentInfo
    {
        //@brief full lane name list of current segment.
        SSD::SimStringVector laneNameList;
        //@brief road id of current segment.
        long roadId;
        //@brief waypoint index at start point.
        int from = -1;
        //@brief waypoint index at end point.
        int to = -1;
    };

	struct LIBEXPORT MRoutePoint {
		MLaneId laneId;
		double centerOffset = 0.0;
		double startS = 0.0;
		double endS = 0.0;
		double offsetEnd = 0.0;  //used by lane change
	};

    struct LIBEXPORT MRoutePath
    {
        //@brief waypoint list.
        SSD::SimPoint3DVector waypoints;
        //@brief tangent list for each waypoint.
        SSD::SimPoint3DVector tangents;
        //@brief MSegmentInfo list for each waypoint.
        SSD::SimVector<MSegmentInfo> segmentInfos;
    };

    struct LIBEXPORT MRoutePathEx
    {
        MRoutePathEx();
        MRoutePathEx(const MRoutePath& _from);
        //@brief waypoint list.
        SSD::SimPoint3DVector waypoints;
        //@brief tangent list for each waypoint.
        SSD::SimPoint3DVector tangents;
        //@brief curvature list for each waypoint.
        SSD::SimVector<double> curvatures;
        //@brief MSegmentInfo list for each waypoint.
        SSD::SimVector<MSegmentInfo> segmentInfos;
    };
}
