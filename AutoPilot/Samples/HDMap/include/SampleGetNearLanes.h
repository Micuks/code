#pragma once

#include "SimOneNetAPI.h"
#include "CloudPlatform.h"
#include <iostream>

using SSD::SimPoint3D;
using SSD::SimString;
using SSD::SimStringVector;

void SampleGetNearLanes(const SimPoint3D& pos, const double& distance)
{
	SimStringVector nearLanes;
	if (!SimOneSM::GetNearLanes(pos, distance, nearLanes))
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "No lanes(lane) are(is) found");
		else
			std::cout << "No lanes(lane) are(is) found." << std::endl;
		return;
	}
	if (CLOUD_PLATFORM)
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "lane id list:");
	else
		std::cout << "lane id list:";
	for (unsigned int i = 0; i < nearLanes.size(); i++)
	{
		const SimString& laneId = nearLanes[i];
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "%s,", laneId.GetString());
		else
			std::cout << laneId.GetString() << ",";
	}
	if (!CLOUD_PLATFORM)
		std::cout << std::endl;
}

