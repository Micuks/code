#pragma once

#include "SimOneNetAPI.h"
#include "CloudPlatform.h"
#include <iostream>

using SSD::SimPoint3D;
using SSD::SimString;
using SSD::SimStringVector;

void SampleGetNearLanesWithAngle(const SimPoint3D& pos,
	const double& distance,
	const double& headingAngle,
	const double& shiftAngle)
{
	SimStringVector nearLanes;
	if (!SimOneSM::GetNearLanesWithAngle(pos, distance, headingAngle, shiftAngle, nearLanes))
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "No lanes(lane) are(is) found.");
		else
			std::cout << "No lanes(lane) are(is) found." << std::endl;
		return;
	}
	if (CLOUD_PLATFORM)
	{
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "nearLanes size: %d", nearLanes.size());
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "lane id list:");	
	}
	else
	{
		std::cout << "nearLanes size:" << nearLanes.size() << std::endl;
		std::cout << "lane id list:";
	}
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

