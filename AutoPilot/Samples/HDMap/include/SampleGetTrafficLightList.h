#pragma once
#include "SimOneNetAPI.h"
#include "CloudPlatform.h"
#include <iostream>

using SSD::SimString;

SSD::SimVector<HDMapStandalone::MSignal> SampleGetTrafficLightList()
{
	SSD::SimVector<HDMapStandalone::MSignal> TrafficLightList;
	SimOneSM::GetTrafficLightList(TrafficLightList);
	if (TrafficLightList.size() < 1)
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "No traffic light exists!");
		else
			std::cout << "No traffic light exists!" << std::endl;
		return TrafficLightList;
	}
	
	for (auto& item : TrafficLightList)
	{
		if (CLOUD_PLATFORM)
		{
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "sign id: %ld", item.id);
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "type: %s", item.type.GetString());
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "subType: %s", item.subType.GetString());
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "item.pt.x: %f, item.pt.y: %f, item.pt.z: %f", item.pt.x, item.pt.y, item.pt.z);
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "heading.pt.x: %f, heading.pt.y: %f, heading.pt.z: %f,", item.heading.x, item.heading.y, item.heading.z);
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "value: %s", item.value.GetString());
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "unit: %s", item.unit.GetString());
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "isDynamic: %d", item.isDynamic);
		}
		else
		{
			std::cout << "sign id:" << item.id << std::endl;
			std::cout << "type:" << item.type.GetString() << std::endl;
			std::cout << "subType:" << item.subType.GetString() << std::endl;
			std::cout << "item.pt.x: " << item.pt.x << "  item.pt.y: " << item.pt.y << "  item.pt.z: " << item.pt.z << std::endl;
			std::cout << "heading.pt.x: " << item.heading.x << "  heading.pt.y: " << item.heading.y << "  heading.pt.z: " << item.heading.y << std::endl;
			std::cout << "value:" << item.value.GetString() << std::endl;
			std::cout << "unit:" << item.unit.GetString() << std::endl;
			std::cout << "isDynamic:" << item.isDynamic << std::endl;
		}
	}
	return TrafficLightList;
}