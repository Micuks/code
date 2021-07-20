#pragma once

#include "SimOneNetAPI.h"
#include "CloudPlatform.h"
#include <iostream>

using SSD::SimString;
using SSD::SimPoint3D;

void SampleContainsLane(const SimString& laneId)
{
	if (!SimOneSM::ContainsLane(laneId))
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "Error: lane does not eixst in the map.");
		else
			std::cout << "Error: lane does not eixst in the map." << std::endl;
		return;
	}
	if (CLOUD_PLATFORM)
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelInformation, "lane exists in the map.");
	else
		std::cout << "lane exists in the map." << std::endl;
}