#pragma once
#include "SimOneNetAPI.h"
#include "CloudPlatform.h"
#include <iostream>

using SSD::SimString;
using SSD::SimPoint3D;

void SampleGetLaneMiddlePoint(const SimPoint3D& pos, const SimString& laneId)
{
	SSD::SimPoint3D targetPoint;
	SSD::SimPoint3D dir;
	bool result = SimOneSM::GetLaneMiddlePoint(pos, laneId, targetPoint, dir);
	if (!result)
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "Not exists!");
		else
			std::cout << "Error: Not exists!" << std::endl;
		return;
	}
	if (CLOUD_PLATFORM)
	{
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "[targetPoint.x: %f,targetPoint.y: %f,targetPoint.z: %f]", targetPoint.x, targetPoint.y, targetPoint.z);
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "[dir.x: %f, dir.y: %f, dir.z: %f]", dir.x, dir.y, dir.z);
	}
	else
	{
		std::cout << "[targetPoint.x: targetPoint.y: targetPoint.y: ]" << targetPoint.x << "," << targetPoint.y << "," << targetPoint.z << std::endl;
		std::cout << "[dir.x: dir.y: dir.y: ]" << dir.x << "," << dir.y << "," << dir.z << std::endl;
	}
}