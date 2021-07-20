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
	enum
	{
		eROAD_ID_UNDEFINED = -1,
		eLANE_ID_UNDEFINED = -99,
		eSECTION_INDEX_UNDEFINED = -1
	};

	struct LIBEXPORT MSignalValidity
	{
		long roadId = eROAD_ID_UNDEFINED;
		int sectionIndex = eSECTION_INDEX_UNDEFINED;
		int fromLaneId = eLANE_ID_UNDEFINED;
		int toLaneId = eLANE_ID_UNDEFINED;
		SSD::SimVector<long> stopLineIds;
		SSD::SimVector<long> crosswalkIds;
	};

	struct LIBEXPORT MSignal
	{
		//@brief signal's id.
		long id;

		//@brief signal's type.
		SSD::SimString type;

		//@brief signal's subType.
		SSD::SimString subType;

		//@brief signal's location defined in localENU.
		SSD::SimPoint3D pt;

		//@brief signal's front-side heading direction defined in localENU.
		SSD::SimPoint3D heading;

		//@brief signal's value, usually used by traffic sign, like limit speed sign.
		SSD::SimString value;

		//@brief signal's value unit, usually used by traffic sign, like limit speed sign.
		SSD::SimString unit;

		//@brief signal's dynamic flag.
		bool isDynamic;

		//@brief signal's physical owner road's id.
		//long roadId;

		//@brief signal's validities.
		SSD::SimVector<MSignalValidity> validities;
	};
}
