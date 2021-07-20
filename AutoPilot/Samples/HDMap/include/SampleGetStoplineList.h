#pragma once
#include "SimOneNetAPI.h"
#include "CloudPlatform.h"
#include <iostream>

using SSD::SimString;
using SSD::SimPoint3D;

void SampleGetStoplineList(const SimString& laneId, SSD::SimVector<HDMapStandalone::MSignal> TrafficLightList)
{
	if (TrafficLightList.size() < 1)
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "No traffic light exists!");
		else
			std::cout << "No traffic light exists!" << std::endl;
		return;
	}
	SSD::SimVector<HDMapStandalone::MObject> stoplineList;
	for (auto&item : TrafficLightList)
	{
		SimOneSM::GetStoplineList(item, laneId, stoplineList);
		for (size_t i = 0; i < stoplineList.size(); i++)
		{
			auto& objectItem = stoplineList[i];
			if (CLOUD_PLATFORM)
			{
				SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "objectItem.id: %ld", objectItem.id);
				SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "objectItem.type: %s", objectItem.type.GetString());
				SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "[pt.x: %f, pt.y: %f, pt.y: %f]", objectItem.pt.x, objectItem.pt.y, objectItem.pt.z);
				SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "objectItem.boundaryKnots: %d", objectItem.boundaryKnots.size());
			}
			else
				{
					std::cout << "objectItem.id :" << objectItem.id << std::endl;
					std::cout << "objectItem.type :" << objectItem.type.GetString() << std::endl;
					std::cout << "[pt.x: pt.y: pt.y: ]" << objectItem.pt.x << "," << objectItem.pt.y << "," << objectItem.pt.z << std::endl;
					std::cout << "objectItem.boundaryKnots :" << objectItem.boundaryKnots.size() << std::endl;
				}
		}
	}
}