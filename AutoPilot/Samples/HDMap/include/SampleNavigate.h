#pragma once
#include "SimOneNetAPI.h"
#include "CloudPlatform.h"
#include <iostream>

using SSD::SimString;

void SampleNavigate(const SSD::SimPoint3DVector& inputPoints)
{
	SSD::SimVector<int> indexOfValidPoints;
	SSD::SimVector<long> roadIdList;
	bool result = SimOneSM::Navigate(inputPoints, indexOfValidPoints, roadIdList);
	if (!result)
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "Not exists!");
		else
			std::cout << "Not exists!" << std::endl;
	}
	for (auto&item: indexOfValidPoints)
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "indexOfValidPoint: %d", item);
		else
			std::cout << "indexOfValidPoint" << item << std::endl;
	}
	for (auto&item : roadIdList)
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "roadId: %ld", item);
		else
			std::cout << "roadId" << item << std::endl;
	}
}
