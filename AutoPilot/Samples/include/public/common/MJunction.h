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
	
	struct LIBEXPORT MJunctionLaneLink
	{
		//@brief link from lane's id.
		int fromLaneId = 0;
		//@brief link to lane's id.
		int toLaneId = 0;
	};

	struct LIBEXPORT MJunctionConnection
	{
		//@brief current connecting road id.
		long connectingRoadId = -1;
		//@brief current incoming road id.
		long incomingRoadId = -1;
		//@brief lane link info.
		SSD::SimVector<MJunctionLaneLink> laneLinks;
	};

	struct LIBEXPORT MJunction
	{
		//@brief junction's id.
		long id;
		//@brief junction's connecting road id list.
		SSD::SimVector<long> connectingRoadIds;
		//@brief junction's incoming road id list.
		SSD::SimVector<long> incomingRoadIds;
		//@brief junction connection info.
		SSD::SimVector<MJunctionConnection> connections;
	};
}
