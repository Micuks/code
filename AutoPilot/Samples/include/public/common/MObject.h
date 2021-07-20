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
	struct LIBEXPORT MObject
	{
		//@brief object's id.
		long id;

		//@brief object's type.
		SSD::SimString type;

		//@brief object's location.
		SSD::SimPoint3D pt;

		//@brief object's boundary knot list.
		SSD::SimPoint3DVector boundaryKnots;

		//@brief object's owner road's id.
		//long roadId;
	};
}
