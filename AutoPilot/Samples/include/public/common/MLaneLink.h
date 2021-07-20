#pragma once

#include "public/libexport.h"
#ifdef STATIC_SSD
#include "SSD/public/SimVector.h"
#include "SSD/public/SimString.h"
#else
#include "SSD/SimVector.h"
#include "SSD/SimString.h"
#endif

namespace HDMapStandalone {
	struct LIBEXPORT MLaneLink
	{
		//@brief lane's predecessors' laneName list, formatted as roadId_sectionIndex_laneId.
		SSD::SimStringVector predecessorLaneNameList;
		//@brief lane's successors' laneName list, formatted as roadId_sectionIndex_laneId.
		SSD::SimStringVector successorLaneNameList;
		//@brief lane's left neighbor's laneName, formatted as roadId_sectionIndex_laneId.
		SSD::SimString leftNeighborLaneName;
		//@brief lane's right neighbor's laneName, formatted as roadId_sectionIndex_laneId.
		SSD::SimString rightNeighborLaneName;
	};
}