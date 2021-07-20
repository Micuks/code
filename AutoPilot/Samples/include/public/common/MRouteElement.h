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

namespace HDMapStandalone {
    typedef SSD::SimVector<double> MDoubleVector;
    struct LIBEXPORT MRouteElement
    {
        //@brief constructor.
        //@param _laneName is the laneName of target lane, formatted as roadId_sectionIndex_laneId.
        MRouteElement(const SSD::SimString& _laneName);

		MRouteElement();

        //@brief destructor.
        ~MRouteElement();

        //@brief r-value copy constructor.
        MRouteElement(MRouteElement&& r) noexcept;

        //@brief copy constructor.
        MRouteElement(const MRouteElement& r) noexcept;

        //@brief assignment.
        MRouteElement& operator=(const MRouteElement& r) noexcept;

        //@brief laneName, formatted as roadId_sectionIndex_laneId.
		SSD::SimString laneName;

        //@brief waypoint list of current route element.
		SSD::SimPoint3DVector waypoints;

        //@brief s value list for each waypoint.
        MDoubleVector sValues;

        //@brief flag of whether this lane allows change lane.
        bool isChangeLane;

        //@brief flag of whether this lane can exit to connect to other road's lane.
        bool canExit;

        //@brief index of passage in topology structure.
        int passageIndex;

        //@brief s value of start waypoint.
        double startS;

        //@brief s value of end waypoint.
        double endS;
    };
}