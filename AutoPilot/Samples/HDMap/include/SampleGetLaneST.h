#pragma once

#include "SimOneNetAPI.h"
#include "CloudPlatform.h"
#include <iostream>

using SSD::SimString;
using SSD::SimPoint3D;

void SampleGetLaneST(const SimString& laneId, const SimPoint3D& pos, double &s, double &t)
{
	//double s, t;
	if (!SimOneSM::GetLaneST(laneId, pos, s, t))
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "Error: lane does not eixst in the map.");
		else
			std::cout << "Error: lane does not eixst in the map." << std::endl;
		return;
	}
	if (CLOUD_PLATFORM)
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "relative to this lane, this location: (%f, %f, %f),s s-t coordidate position: [s: %f, t: %f]", pos.x, pos.y, pos.z, s, t);
	else
		std::cout << "relative to this lane, this location(" << pos.x
			<< "," << pos.y
			<< "," << pos.z
			<< ") "
			<< "'s s-t coordidate position [s, t]:" << s
			<< "," << t
			<< std::endl;
}