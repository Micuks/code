#pragma once
#include "SimOneNetAPI.h"
#include "CloudPlatform.h"
#include <iostream>

using SSD::SimString;

void SampleGetHeights(const SSD::SimPoint3D& inputPt, double radius)
{
	SSD::SimVector<double> heights;
	SSD::SimVector<long> roadIds;
	SSD::SimVector<bool> insideRoadStates;
	bool result = SimOneSM::GetHeights(inputPt, radius, heights, roadIds, insideRoadStates);
	if (!result)
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "not exist");
		else
			std::cout << "not exist" << std::endl;
		return;
	}
	for (auto&item : heights)
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "height: %f", item);
		else
			std::cout << "height : " << item << std::endl;
	}
	for (auto&item : roadIds)
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "roadId: %ld", item);
		else
			std::cout << "roadId : " << item << std::endl;
	}
	for (auto&item : insideRoadStates)
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "insideRoadState: %d", item);
		else
			std::cout << "insideRoadState : " << item << std::endl;
	}
}
