#pragma once

#include "public/libexport.h"
#include "SSD/SimString.h"
#include "SSD/SimPoint3D.h"
#include "MRoadMark.h"

namespace HDMapStandalone {

	struct LIBEXPORT MParkingSpaceMarking
	{
		//@brief marking's side.
		SSD::SimString side;

		//@brief marking's type.
		ERoadMarkType type = ERoadMarkType::none;

		//@brief marking's color.
		ERoadMarkColor color = ERoadMarkColor::standard;

		//@brief marking's line width.
		double width = 0.13;
	};

	struct LIBEXPORT MParkingSpace
	{
		//@brief object's id.
		long id;

		//@brief owner road's id.
		long roadId;

		//@brief object's location.
		SSD::SimPoint3D pt;

		//@brief heading direction, always fuzzy align with 'front' direction.
		SSD::SimPoint3D heading;

		//@brief parking space's boundary knot list. Assume knot order is [knot_a, knot_b, knot_c, knot_d] as anticlockwise.
		//segment{knot_a, knot_d} represents 'front', usually as a valid entrance that a car can enter into the parkingSpace.
		//segment{knot_a, knot_b} represnets 'left'.
		//segment{knot_b, knot_c} represnets 'rear'.
		//segment{knot_c, knot_d} represnets 'right'.
		SSD::SimPoint3DVector boundaryKnots;

		//@brief front marking.
		MParkingSpaceMarking front;

		//@brief rear marking.
		MParkingSpaceMarking rear;

		//@brief left marking.
		MParkingSpaceMarking left;

		//@brief right marking.
		MParkingSpaceMarking right;
	};
}
