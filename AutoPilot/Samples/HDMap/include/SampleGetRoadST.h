#pragma once

#include "SimOneNetAPI.h"
#include "CloudPlatform.h"
#include <iostream>


using SSD::SimString;
using SSD::SimPoint3D;

void SampleGetRoadST(const SimString& laneId, const SimPoint3D& pos)
{
	double s, t, z;
	if (!SimOneSM::GetRoadST(laneId, pos, s, t, z))
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "Error: lane does not eixst in the map");
		else
			std::cout << "Error: lane does not eixst in the map." << std::endl;
		return;
	}
	if (CLOUD_PLATFORM)
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "relative to this lane's owner road, this location: (%f, %f, %f), s-t coordidate position: [s: %f,t: %f]", pos.x, pos.y, pos.z, s, t);
	else
		std::cout << "relative to this lane's owner road, this location(" << pos.x
			<< "," << pos.y
			<< "," << pos.z
			<< ") "
			<< "'s s-t coordidate position [s, t]:"
			<< s
			<< "," << t
			<< std::endl;
}