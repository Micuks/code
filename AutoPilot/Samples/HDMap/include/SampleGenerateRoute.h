#pragma once

#include "SimOneNetAPI.h"
#include "CloudPlatform.h"
#include <iostream>

void SampleGenerateRoute()
{
	SSD::SimPoint3DVector route;
	SSD::SimPoint3DVector inputPoints;
	inputPoints.push_back(SSD::SimPoint3D(-135.477, 52.329, 0));
	inputPoints.push_back(SSD::SimPoint3D(-48.290, -18.109, 0));
	SSD::SimVector<int> indexOfValidPoints;
	if (!SimOneSM::GenerateRoute(inputPoints, indexOfValidPoints, route))
	{
		if (CLOUD_PLATFORM)
		{
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "Error: route is not generated in the map.");
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "indexOfValidPoints:");
		}
		else
		{
			std::cout << "Error: route is not generated in the map." << std::endl;
			std::cout << "indexOfValidPoints:";
		}
		for (auto& index : indexOfValidPoints)
		{
			if (CLOUD_PLATFORM)
				SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, " %d,", index);
			else
				std::cout << index << ",";
		}
		if (!CLOUD_PLATFORM)
			std::cout << std::endl;
		return;
	}
	if (CLOUD_PLATFORM)
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "route size: %d", route.size());
	else
		std::cout << "route size:" << route.size() << std::endl;
	for (unsigned int i = 0; i < route.size(); i++)
	{
		auto& knot = route[i];
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "( %f, %f, %f),", knot.x, knot.y, knot.z);
		else
			std::cout << "(" << knot.x << ","<< knot.y << ","<< knot.z << "),";
	}
	if (!CLOUD_PLATFORM)
		std::cout << std::endl;
}