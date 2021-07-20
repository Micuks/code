#pragma once

#include "public/libexport.h"
#include "SSD/SimString.h"

namespace HDMapStandalone {
	class LIBEXPORT MLaneId
	{
	public:
		//@brief default constructor.
		MLaneId();

		//@brief constructor.
		MLaneId(const SSD::SimString& laneName);

		//@brief convert it to string with this format: roadId_sectionIndex_laneId.
		SSD::SimString ToString() const;

	public:
		//@brief road id that this lane belogs to.
		long roadId;

		//@brief index of current section in road.
		int sectionIndex;

		//@brief lane id that aligns with openDrive definition of lane id.
		int laneId;
	};
}