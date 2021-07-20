#pragma once
#include "SimOneNetAPI.h"
#include "CloudPlatform.h"
#include <iostream>

using SSD::SimString;
using SSD::SimPoint3D;

void SampleGetCrosswalkList(const SimPoint3D& pos, const SimString& laneId, SSD::SimVector<HDMapStandalone::MSignal> TrafficLightList)
{
	if (TrafficLightList.size() < 1) 
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "No traffic light exists!");
		else
			std::cout << "No traffic light exists!" << std::endl;
		return;
	}
	SSD::SimVector<HDMapStandalone::MObject> crosswalkList;
	for (auto&item : TrafficLightList)
	{
		SimOneSM::GetCrosswalkList(item, laneId, crosswalkList);
		for (size_t i = 0; i < crosswalkList.size(); i++)
		{
			auto& objectItem = crosswalkList[i];
			if (CLOUD_PLATFORM)
			{
				SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "objectItem.id: %ld", objectItem.id);
				SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "objectItem.type: %s", objectItem.type.GetString());
				SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "objectItem.pt.x: %f, objectItem.pt.y: %f, objectItem.pt.z: %f", objectItem.pt.x, objectItem.pt.y, objectItem.pt.z);
				SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "objectItem.boundaryKnots: %d", objectItem.boundaryKnots.size());
			}
			else
			{
				std::cout << "objectItem.id :" << objectItem.id << std::endl;
				std::cout << "objectItem.type :" << objectItem.type.GetString() << std::endl;
				std::cout << "objectItem.pt.x: " << objectItem.pt.x << "  objectItem.pt.y: " << objectItem.pt.y << "  objectItem.pt.z: " << objectItem.pt.z << std::endl;
				std::cout << "objectItem.boundaryKnots :" << objectItem.boundaryKnots.size() << std::endl;
			}
		}
	}
}