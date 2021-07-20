#pragma once

#include "SimOneNetAPI.h"
#include "CloudPlatform.h"
#include <iostream>

using SSD::SimString;
using SSD::SimPoint3D;

void SampleGetLaneWidth(const SimString& laneId, const SimPoint3D& pos)
{
	double width;
	if (!SimOneSM::GetLaneWidth(laneId, pos, width))
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "Error: lane does not eixst in the map.");
		else
			std::cout << "Error: lane does not eixst in the map." << std::endl;
		return;
	}
	if (CLOUD_PLATFORM)
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "lane width at this location: (%f, %f, %f)", pos.x, pos.y, pos.z);
	else
		std::cout << "lane width at this location(" << pos.x<< "," << pos.y<< "," << pos.z<< ") is:"<< width<< std::endl;
}