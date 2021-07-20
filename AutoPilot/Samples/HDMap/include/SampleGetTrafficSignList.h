#pragma once
#include "SimOneNetAPI.h"
#include "CloudPlatform.h"
#include <iostream>

using SSD::SimString;

void SampleGetTrafficSignList()
{
	SSD::SimVector<HDMapStandalone::MSignal> signList;
	SimOneSM::GetTrafficSignList(signList);
	if (signList.size() < 1)
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "no trafficSign");
		else
			std::cout << "no trafficSign" << std::endl;
		return;
	}
	for (size_t i = 0; i < signList.size(); i++)
	{
		HDMapStandalone::MSignal sign = signList[i];
		if (CLOUD_PLATFORM)
		{
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "sign id: %ld", sign.id);
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "sign.type: %s", sign.type.GetString());
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "sign.subType: %s", sign.subType.GetString());
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "[sign.pt.x: %f, sign.pt.y: %f, sign.pt.z: %f]", sign.pt.x, sign.pt.y, sign.pt.z);
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "[sign.heading.x: %f, sign.heading.y: %f, sign.heading.y: %f]", sign.heading.x, sign.heading.y, sign.heading.z);
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "sign.value: %s", sign.value.GetString());
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "sign.unit: %s", sign.unit.GetString());
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "sign.isDynamic: %d", sign.isDynamic);
		}
		else
		{
			std::cout << "sign id:" << sign.id << std::endl;
			std::cout << "sign.type:" << sign.type.GetString() << std::endl;
			std::cout << "sign.subType:" << sign.subType.GetString() << std::endl;
			std::cout << "[sign.pt.x: sign.pt.y: sign.pt.z: ]" << sign.pt.x << "," << sign.pt.y << "," << sign.pt.z << std::endl;
			std::cout << "[sign.heading.x: sign.heading.y: sign.heading.y: ]" << sign.heading.x << "," << sign.heading.y << "," << sign.heading.z << std::endl;
			std::cout << "sign.value:" << sign.value.GetString() << std::endl;
			std::cout << "sign.unit:" << sign.unit.GetString() << std::endl;
			std::cout << "sign.isDynamic:" << sign.isDynamic << std::endl;
		}
	}

}
