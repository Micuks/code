#pragma once

#include "SimOneNetAPI.h"
#include "public/common/MLaneLink.h"
#include "CloudPlatform.h"
#include <iostream>

using SSD::SimString;

void SampleGetLaneLink(const SimString& laneId)
{
	MLaneLink link;
	if (!SimOneSM::GetLaneLink(laneId, link))
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "Error: lane does not eixst in the map");
		else
			std::cout << "Error: lane does not eixst in the map." << std::endl;
		return;
	}
	if (CLOUD_PLATFORM)
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "predecessor lane Id list:");
	else
		std::cout << "predecessor lane Id list:" << std::endl;
	for (unsigned int i = 0; i < link.predecessorLaneNameList.size(); i++)
	{
		const SimString& laneId = link.predecessorLaneNameList[i];
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, " %s,", laneId.GetString());
		else
			std::cout << laneId.GetString() << ",";
	}
	if (!CLOUD_PLATFORM)
		std::cout << std::endl;

	if (CLOUD_PLATFORM)
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "successor lane Id list:");
	else
		std::cout << "successor lane Id list:" << std::endl;
	for (unsigned int i = 0; i < link.successorLaneNameList.size(); i++)
	{
		const SimString& laneId = link.successorLaneNameList[i];
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, " %s,", laneId.GetString());
		else
			std::cout << laneId.GetString() << ",";
	}
	if (CLOUD_PLATFORM)
	{
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "left neighbor Id: %s", link.leftNeighborLaneName.GetString());
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "right neighbor Id: %s", link.rightNeighborLaneName.GetString());
	}
	else
	{
		std::cout << "left neighbor Id:" << link.leftNeighborLaneName.GetString() << std::endl;
		std::cout << "right neighbor Id:" << link.rightNeighborLaneName.GetString() << std::endl;
	}
}