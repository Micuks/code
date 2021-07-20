#pragma once

#include "SimOneNetAPI.h"
#include "public/common/MLaneInfo.h"
#include "CloudPlatform.h"
#include <iostream>

using namespace HDMapStandalone;
using SSD::SimPoint3D;
using SSD::SimString;

void SampleGetLaneSample(const SimString& laneId)
{
	double s, t, s_toCenterLine, t_toCenterLine;
	MLaneInfo info;
	if (!SimOneSM::GetLaneSample(laneId, info))
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "Error: lane does not eixst in the map.");
		else
			std::cout << "Error: lane does not eixst in the map." << std::endl;
		return;
	}
	if (CLOUD_PLATFORM)
	{
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "left boundary knot size: %d", info.leftBoundary.size());
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "left boundary knot list:");
	}
	else {
		std::cout << "left boundary knot size:" << info.leftBoundary.size() << std::endl;
		std::cout << "left boundary knot list:" << std::endl;
	}
	for (unsigned int i = 0; i < info.leftBoundary.size(); i++)
	{
		const SimPoint3D& knot = info.leftBoundary[i];
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "( %f, %f, %f),", knot.x, knot.y, knot.z);
		else
			std::cout << "(" << knot.x << ","<< knot.y << ","<< knot.z << "),";
	}
	if (CLOUD_PLATFORM)
	{
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "right boundary knot size: %d", info.rightBoundary.size());
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "right boundary knot list:");
	}
	else {
		std::cout << std::endl;
		std::cout << "right boundary knot size:" << info.rightBoundary.size() << std::endl;
		std::cout << "right boundary knot list:" << std::endl;
	}
	for (unsigned int i = 0; i < info.rightBoundary.size(); i++)
	{
		const SimPoint3D& knot = info.rightBoundary[i];
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "( %f, %f, %f),", knot.x, knot.y, knot.z);
		else
			std::cout << "(" << knot.x << ","<< knot.y << ","<< knot.z << "),";
	}
	if (CLOUD_PLATFORM)
	{
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "center line knot size: %d", info.centerLine.size());
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "center line knot list:");
	}
	else
	{
		std::cout << std::endl;
		std::cout << "center line knot size:" << info.centerLine.size() << std::endl;
		std::cout << "center line knot list:" << std::endl;
	}
	for (unsigned int i = 0; i < info.centerLine.size(); i++)
	{
		const SimPoint3D& knot = info.centerLine[i];
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "( %f, %f, %f),", knot.x, knot.y, knot.z);
		else
			std::cout << "(" << knot.x << ","<< knot.y << ","<< knot.z << "),";
	}
	if (!CLOUD_PLATFORM)
		std::cout << std::endl;
}