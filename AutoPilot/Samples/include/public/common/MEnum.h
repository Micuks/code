#pragma once

#include "public/libexport.h"

namespace HDMapStandalone {

	//@brief When loading xodr gets failed, LoadData() will report error code.
	//eNotLocalENU - the system only accepts xodr based on localENU.
	//eInvalidVersion - xodr is not a valid version.
	//eEmptyRoad - xodr does not have any road.
	//eInvalidData - xodr contains invalid data that may cause runtime exception.
	enum class MLoadErrorCode
	{
		eNotLocalENU,
		eInvalidVersion,
		eEmptyRoad,
		eInvalidData
	};

	//@brief When loading xodr, need to specify xodr's data type.
	//eXodrFile - xodr file, as file name, and geographic info is LocalENU only.
	//eXodrContent - xodr content, and geographic info is localENU only.
	//eDBContent - xodr data is from database.
	enum class MXodrSourceType
	{
		eXodrFile,
		eXodrContent,
		eDBContent
	};

	//@brief enum type definition of lane type. Its value set perfectly matches with opendrive format.
	enum class MLaneType
	{
		none,
		driving,
		stop,
		shoulder,
		biking,
		sidewalk,
		border,
		restricted,
		parking,
		bidirectional,
		median,
		special1,
		special2,
		special3,
		roadWorks,
		tram,
		rail,
		entry,
		exit,
		offRamp,
		onRamp,
		mwyEntry,
		mwyExit
	};

	enum class MSideState
	{
		eLeftSide,
		eInner,
		eRightSide
	};

	enum class MInsideType
	{
		eInsideLane,
		eInsideParkingSpace,
		eNA
	};
}