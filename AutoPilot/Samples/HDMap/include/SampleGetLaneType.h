#pragma once

#include "SimOneNetAPI.h"
#include "CloudPlatform.h"
#include <iostream>

using SSD::SimString;

void SampleGetLaneType(const SimString& laneId)
{
	HDMapStandalone::MLaneType type;
	if (!SimOneSM::GetLaneType(laneId, type))
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "Error: lane does not eixst in the map");
		else
			std::cout << "Error: lane does not eixst in the map." << std::endl;
		return;
	}
	std::string typeStr;
	switch (type)
	{
		case MLaneType::none:
		{
			typeStr = "MLaneType::none";
		}
		break;
		case MLaneType::driving:
		{
			typeStr = "MLaneType::driving";
		}
		break;
		case MLaneType::stop:
		{
			typeStr = "MLaneType::stop";
		}
		break;
		case MLaneType::shoulder:
		{
			typeStr = "MLaneType::shoulder";
		}
		break;
		case MLaneType::biking:
		{
			typeStr = "MLaneType::biking";
		}
		break;
		case MLaneType::sidewalk:
		{
			typeStr = "MLaneType::sidewalk";
		}
		break;
		case MLaneType::border:
		{
			typeStr = "MLaneType::border";
		}
		break;
		case MLaneType::restricted:
		{
			typeStr = "MLaneType::restricted";
		}
		break;
		case MLaneType::parking:
		{
			typeStr = "MLaneType::parking";
		}
		break;
		case MLaneType::bidirectional:
		{
			typeStr = "MLaneType::bidirectional";
		}
		break;
		case MLaneType::median:
		{
			typeStr = "MLaneType::median";
		}
		break;
		case MLaneType::special1:
		{
			typeStr = "MLaneType::special1";
		}
		break;
		case MLaneType::special2:
		{
			typeStr = "MLaneType::special2";
		}
		break;
		case MLaneType::special3:
		{
			typeStr = "MLaneType::special3";
		}
		break;
		case MLaneType::roadWorks:
		{
			typeStr = "MLaneType::roadWorks";
		}
		break;
		case MLaneType::tram:
		{
			typeStr = "MLaneType::tram";
		}
		break;
		case MLaneType::rail:
		{
			typeStr = "MLaneType::rail";
		}
		break;
		case MLaneType::entry:
		{
			typeStr = "MLaneType::entry";
		}
		break;
		case MLaneType::exit:
		{
			typeStr = "MLaneType::exit";
		}
		break;
		case MLaneType::offRamp:
		{
			typeStr = "MLaneType::offRamp";
		}
		break;
		case MLaneType::onRamp:
		{
			typeStr = "MLaneType::onRamp";
		}
		break;
		case MLaneType::mwyEntry:
		{
			typeStr = "MLaneType::mwyEntry";
		}
		break;
		case MLaneType::mwyExit:
		{
			typeStr = "MLaneType::mwyExit";
		}
		break;
		default:
			typeStr = "MLaneType::none";
	}
	if (CLOUD_PLATFORM)
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "lane type: %s", typeStr.c_str());
	else
		std::cout << "lane type:" << typeStr.c_str() << std::endl;
}