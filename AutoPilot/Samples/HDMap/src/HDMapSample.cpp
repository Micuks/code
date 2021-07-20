#pragma once

#include "SimOneNetAPI.h"
#include "SSD/SimPoint3D.h"
#include "SSD/SimString.h"

#include "SampleGetNearMostLane.h"
#include "SampleGetNearLanes.h"
#include "SampleGetNearLanesWithAngle.h"
#include "SampleGetDistanceToLaneBoundary.h"
#include "SampleGetLaneSample.h"
#include "SampleGetLaneLink.h"
#include "SampleGetLaneType.h"
#include "SampleGetLaneWidth.h"
#include "SampleGetLaneST.h"
#include "SampleGetRoadST.h"
#include "SampleContainsLane.h"
#include "SampleGenerateRoute.h"
#include "SampleGetCrossHatchList.h"
#include "SampleGetTrafficLightList.h"
#include "SampleGetCrosswalkList.h"
#include "SampleGetHeights.h"
#include "SampleGetInertialFromLaneST.h"
#include "SampleGetLaneMiddlePoint.h"
#include "SampleGetParkingSpaceList.h"
#include "SampleGetPredefinedRoute.h"
#include "SampleGetRoadMark.h"
#include "SampleGetStoplineList.h"
#include "SampleGetTrafficSignList.h"
#include "SampleNavigate.h"

#include <chrono>
#include <thread>
#define M_PI        3.14159265358979323846

void SamplesHDMapByLocation(const SSD::SimPoint3D& pos)
{
	std::cout.precision(8);
	//1. GetNearMostLane
	SSD::SimString laneId = SampleGetNearMostLane(pos);
	if (CLOUD_PLATFORM)
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "laneId: %s", laneId.GetString());
	else
		std::cout << "laneId :" << laneId.GetString()<< std::endl;
	//2. GetNearLanes
	SampleGetNearLanes(pos, 5);
	//3. GetNearLanesWithAngle
	double headingAngle = M_PI / 180 * 30;
	double shiftAngle = M_PI / 180 * 90;
	SampleGetNearLanesWithAngle(pos, 5, headingAngle, shiftAngle);
	//4. GetDistanceToLaneBoundary
	SampleGetDistanceToLaneBoundary(pos);
	//5. GetLaneSample
	SampleGetLaneSample(laneId);
	//6. GetLaneLink
	SampleGetLaneLink(laneId);
	//7. GetLaneType
	SampleGetLaneType(laneId);
	//8. GetLaneWidth
	SampleGetLaneWidth(laneId, pos);
	//9. GetLaneST
	double s = 0;
	double t = 0;
	SampleGetLaneST(laneId, pos, s, t);
	//10. GetRoadST
	SampleGetRoadST(laneId, pos);
	//11. ContainsLane
	SampleContainsLane(laneId);
	//12. GetCrossHatchList
	SampleGetCrossHatchList(laneId);
	//13. GetTrafficLightList
	SSD::SimVector<HDMapStandalone::MSignal> trafficLight = SampleGetTrafficLightList();
	//14. GetCrosswalkList
	SampleGetCrosswalkList(pos, laneId, trafficLight);
	//15. GetHeights
	SampleGetHeights(pos, 10.0);
	//16. GetInertialFromLaneST
	SampleGetInertialFromLaneST(laneId, s, t);
	//17. GetLaneMiddlePoint
	SampleGetLaneMiddlePoint(pos, laneId);
	//18. GetParkingSpaceList
	SSD::SimVector<HDMapStandalone::MParkingSpace> parkSpace = SampleGetParkingSpaceList();
	std::cout << "parkSpace =" << parkSpace.size() << std::endl;
	//19. GetPredefinedRoute
	SampleGetPredefinedRoute();
	//20. GetRoadMark
	SampleGetRoadMark(laneId, pos);
	//21. GetStoplineList
	SampleGetStoplineList(laneId, trafficLight);
	//22. GetTrafficSignList
	SampleGetTrafficSignList();
	//23. Navigate
	SSD::SimPoint3DVector inputPoints;
	inputPoints.push_back(SSD::SimPoint3D(-63.999936, 1.955949, 0));
	inputPoints.push_back(SSD::SimPoint3D(123.502658, 1.482458, 0));
	SampleNavigate(inputPoints);
	//24 .GenerateRoute
	SampleGenerateRoute();
}

void gpsCB(int mainVehicleID, SimOne_Data_Gps *gps)
{
	if (CLOUD_PLATFORM)
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "gpsCB: V: %d, GPS: %lld, pos:(%f, %f, %f)", mainVehicleID,
			gps->timestamp, gps->posX, gps->posY, gps->posZ);
	else
		std::cout << "gpsCB: V:" << mainVehicleID
			<< " GPS:" << gps->timestamp
			<< " pos:(" << gps->posX
			<< "," << gps->posY
			<< "," << gps->posZ
			<< ")"
			<< std::endl;

	//HDMap samples based on gps location
	SSD::SimPoint3D pos(gps->posX, gps->posY, gps->posZ);
	SamplesHDMapByLocation(pos);
}

void SamplesGenerateRoute()
{
	SampleGenerateRoute();
}

int main(int argc, char* argv[])
{
	SimOneSM::Start();
	//SimOneAPI::StartSimOneNode(0,0,0);
	//while (true)
	//{
	//	if (SimOneAPI::SubMainVehicle(0))
	//		break;
	//}
	int timeout = 20;
	if (!SimOneSM::LoadHDMap(timeout))
	{
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "Failed to load hdmap!");
		else
			std::cout << "Failed to load hdmap!" << std::endl;
		return 0;
	}

	// Usage1. Samples of using HDMap by specifying location.
	/*SSD::SimPoint3D pos(0.0, 0.0, 0.0);
	SamplesHDMapByLocation(pos);*/

	// Usage2. Get position (of Ego e.g.) from sensers.
	std::unique_ptr<SimOne_Data_Gps> pGPS = std::make_unique<SimOne_Data_Gps>();
	SimOneSM::SetGpsUpdateCB(gpsCB);
	while (1)
	{
		if (!SimOneSM::GetGps(0/*vehicleId*/, pGPS.get()))
		{
			if (CLOUD_PLATFORM)
				SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "Fetch GPS failed!");
			else
				std::cout << "Fetch GPS failed!" << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
    return 0;
}

