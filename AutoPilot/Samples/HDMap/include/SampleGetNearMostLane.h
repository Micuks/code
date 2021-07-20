#pragma once

#include "SimOneNetAPI.h"
#include "CloudPlatform.h"
#include <iostream>

using SSD::SimPoint3D;
using SSD::SimString;

SimString SampleGetNearMostLane(const SimPoint3D& pos)
{
	SimString laneId;
	double s, t, s_toCenterLine, t_toCenterLine;
	if (!SimOneSM::GetNearMostLane(pos, laneId, s, t, s_toCenterLine, t_toCenterLine))
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "Error: lane is not found.");
		else
			std::cout << "Error: lane is not found." << std::endl;
		return laneId;
	}
	if (CLOUD_PLATFORM)
	{
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "lane id: %s", laneId.GetString());
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "[s: %f, t: %f]", s,t);
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "[s_toCenterLine: %f, t_toCenterLine: %f]", s_toCenterLine, t_toCenterLine);
	}
	else
	{
		std::cout << "lane id:" << laneId.GetString() << std::endl;
		std::cout << "[s, t]:" << s << "," << t << std::endl;
		std::cout << "[s_toCenterLine, t_toCenterLine]:" << s_toCenterLine << "," << t_toCenterLine << std::endl;
	}
	return laneId;
}

