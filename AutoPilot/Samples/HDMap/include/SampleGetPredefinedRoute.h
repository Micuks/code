#pragma once
#include "SimOneNetAPI.h"
#include "CloudPlatform.h"
#include <iostream>

using SSD::SimString;
using SSD::SimPoint3D;

void SampleGetPredefinedRoute()
{
	SSD::SimPoint3DVector routeInfo;
	/*routeInfo.push_back(SSD::SimPoint3D(-195.5, -3.000025, 0));
	routeInfo.push_back(SSD::SimPoint3D(172.493987, -2.731247, 0));*/
	bool resule = SimOneSM::GetPredefinedRoute(routeInfo);
	if (!resule)
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "Not exists!");
		else
			std::cout << "Not exists!" << std::endl;
	} 
	for (size_t i = 0; i < routeInfo.size(); i++)
	{
		auto &item = routeInfo[i];
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "[item.x: %f, item.y: %f, item.y: %f]", item.x, item.y, item.z);
		else
			std::cout << "[item.x: item.y: item.y: ]" << item.x << "," << item.y << "," << item.z << std::endl;
	}
}