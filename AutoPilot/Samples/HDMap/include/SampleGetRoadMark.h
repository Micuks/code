#pragma once
#include "SimOneNetAPI.h"
#include "CloudPlatform.h"
#include <iostream>

using SSD::SimString;
using SSD::SimPoint3D;

void SampleGetRoadMark(const SimString& laneId, const SimPoint3D& pos)
{
	HDMapStandalone::MRoadMark left;
	HDMapStandalone::MRoadMark right;
	bool result = SimOneSM::GetRoadMark(pos, laneId, left, right);
	if (result)
	{
		if (CLOUD_PLATFORM)
		{
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "left.sOffset: %f", left.sOffset);
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "left.width: %f", left.width);
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "left.type: %d", (int)left.type);
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "left.color: %d", (int)left.color);
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "right.sOffset: %f", right.sOffset);
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "right.width: %f", right.width);
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "left.type: %d", (int)left.type);
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "left.color: %d", (int)left.color);
		}
		else
		{
			std::cout << "left.sOffset: " << left.sOffset << std::endl;
			std::cout << "left.width: " << left.width << std::endl;
			std::cout << "left.type: " << (int)left.type << std::endl;
			std::cout << "left.color: " << (int)left.color << std::endl;
			std::cout << "right.sOffset: " << right.sOffset << std::endl;
			std::cout << "right.width: " << right.width << std::endl;
			std::cout << "left.type: " << (int)right.type << std::endl;
			std::cout << "left.color: " << (int)right.color << std::endl;
		}
		
	}
	else
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "Not exists!");
		else
			std::cout << "Not exists!" << std::endl;
		return;
	}

}
