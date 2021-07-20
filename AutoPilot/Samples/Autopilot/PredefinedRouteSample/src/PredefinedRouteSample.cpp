#include <iostream>
#include <vector>

#include "SSD/SimPoint3D.h"
#include "SSD/SimString.h"
#include "public/common/MLaneInfo.h"
#include "../HDMap/include/SampleGetNearMostLane.h"
#include "public/common/MLaneId.h"
#include "util/UtilDriver.h"
#include "utilStartSimOneNode.h"

#include <CloudPlatform.h>

using namespace HDMapStandalone;

SimOne_Data_Gps Gps = SimOne_Data_Gps();
std::unique_ptr<SimOne_Data_WayPoints> pWaypoints = std::make_unique<SimOne_Data_WayPoints>();
SimOne_Data_CaseInfo pCaseInfoTest = SimOne_Data_CaseInfo();

void getTargetPath(const SSD::SimPoint3D pos, SSD::SimPoint3DVector &route)
{
	if (SimOneSM::GetWayPoints(pWaypoints.get()))
	{
		if (CLOUD_PLATFORM)
		{
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "wayPointsSize:%s", pWaypoints->wayPointsSize);
		}
		else
			std::cout << "wayPointsSize:" << pWaypoints->wayPointsSize << std::endl;

		//std::cout << "wayPointsSize:" << pWaypoints->wayPointsSize << std::endl;
		if ((pWaypoints->wayPointsSize) >= 2) {
			//SSD::SimPoint3DVector route;
			if (SimOneSM::GetPredefinedRoute(route)) {
				if (CLOUD_PLATFORM)
					SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "route path size:%d", route.size());
				else
					std::cout << "route path size:" << route.size() << std::endl;
			}
		}
		else {
			//SSD::SimPoint3D pos(Gps.posX, Gps.posY, Gps.posZ);
			SSD::SimString laneId = SampleGetNearMostLane(pos);
			HDMapStandalone::MLaneInfo info;
			if (SimOneSM::GetLaneSample(laneId, info)) {
				route = info.centerLine;
			}
		}
	}
	else {
		if (CLOUD_PLATFORM)
		{
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "mainVehicle not set path !!!");
		}
		else
			std::cout << "mainVehicle not set path !!!" << std::endl;
	}
}

double calculateSteering(const SSD::SimPoint3DVector& targetPath, SimOne_Data_Gps *pGps, int& lastTargetPathIndex)
{
	std::vector<float> pts;
	for (int i = 0; i < targetPath.size(); ++i)
	{
		pts.push_back(pow((pGps->posX - targetPath[i].x), 2) + pow((pGps->posY - targetPath[i].y), 2));
	}
	int index = min_element(pts.begin(), pts.end()) - pts.begin();
	if (CLOUD_PLATFORM)
	{
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "lastTargetPathIndex:%d", lastTargetPathIndex);
		SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "first index::%d", index);
	}
	else
		std::cout << "lastTargetPathIndex:" << lastTargetPathIndex << std::endl;
		std::cout << "first index:" << index << std::endl;

	while (1) {
		if (index >= lastTargetPathIndex) {
			lastTargetPathIndex = index;
			break;
		}
		else {
			if (pts.size() > 0) {
				pts.erase(pts.begin() + index);
				index = min_element(pts.begin(), pts.end()) - pts.begin();
			}
		}
	}


	int forwardIndex = 0;
	float MinProgDist = 3.;
	float ProgTime = 0.8;
	float MainVehicleSpeed = sqrtf(pGps->velX * pGps->velX + pGps->velY * pGps->velY + pGps->velZ * pGps->velZ);
	float progDist = MainVehicleSpeed * ProgTime > MinProgDist ? MainVehicleSpeed * ProgTime : MinProgDist;

	for (; index < targetPath.size(); ++index)
	{
		forwardIndex = index;
		float distance = sqrtf(pow(targetPath[index].x - pGps->posX, 2) + pow(targetPath[index].y - pGps->posY, 2));
		if (distance >= progDist)
		{
			break;
		}
	}

	double psi = static_cast<double>(pGps->oriZ);
	double Alfa = atan2(targetPath[forwardIndex].y - pGps->posY, targetPath[forwardIndex].x - pGps->posX) - psi;
	double ld = static_cast<double>(sqrt(pow(targetPath[forwardIndex].y - pGps->posY, 2) + pow(targetPath[forwardIndex].x - pGps->posX, 2)));
	double steering = static_cast<double>(-atan2(2. * (1.3 + 1.55) * sin(Alfa), ld) * 36. / (7. * M_PI));
	return steering;
}

//Main function
//
int main()
{
	StartSimOne::WaitSimOneIsOk(true);

	//Wait for the Sim-One case to run
	while (1) {
		int frame = SimOneAPI::Wait();
		SimOneAPI::GetSimOneGps(&Gps);
		if (SimOneAPI::GetCaseRunStatus() == SimOne_Case_Status::SimOne_Case_Status_Running && (Gps.timestamp > 0)) {
			if (CLOUD_PLATFORM)
				SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "SimOne Initialized");
			else
				printf("SimOne Initialized\n");
			SimOneAPI::NextFrame(frame);
			break;
		}
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "SimOne Initializing...");
		else
			printf("SimOne Initializing...\n");
	}

	//load Map Data
	int timeout = 20;
	bool slowDown = false;
	int obstacltFlag = 0;
	if (!SimOneSM::LoadHDMap(timeout)) {
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "Failed to load map!");
		else
			std::cout << "Failed to load map!" << std::endl;
		return 0;
	}

	SSD::SimPoint3DVector route;
	SSD::SimPoint3D pos(Gps.posX, Gps.posY, Gps.posZ);
	getTargetPath(pos, route);

	if (SimOneSM::GetWayPoints(pWaypoints.get()))
	{
		std::cout << "wayPointsSize:" << pWaypoints->wayPointsSize << std::endl;
		if ((pWaypoints->wayPointsSize) >= 2) {
			SSD::SimPoint3DVector route;
			if (SimOneSM::GetPredefinedRoute(route)) {
				if (CLOUD_PLATFORM)
					SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "route path size:%d\n", route.size());
				else
					std::cout << "route path size:" << route.size() << std::endl;
			}
		}
		else {
			SSD::SimPoint3D pos(Gps.posX, Gps.posY, Gps.posZ);
			SSD::SimString laneId = SampleGetNearMostLane(pos);
			HDMapStandalone::MLaneInfo info;
			if (SimOneSM::GetLaneSample(laneId, info)) {
				SSD::SimPoint3DVector route = info.centerLine;
			}

		}
	}
	else {
		std::cout << "mainVehicle not set path !!!" << std::endl;
	}
		

	SSD::SimPoint3DVector route;
	if (SimOneSM::GetPredefinedRoute(route)) {
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "route path size:%d\n", route.size());
		else
			std::cout << "route path size:" << route.size() << std::endl;
	}

	while (1)
	{
		//exit
		if (SimOneAPI::GetCaseRunStatus() == SimOne_Case_Status::SimOne_Case_Status_Stop) {
			break;
		}
		//感知
		int frame = SimOneAPI::Wait();
		if (!SimOneAPI::GetSimOneGps(&Gps)) {
			if (CLOUD_PLATFORM)
				SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "Fetch GPS failed");
			else
				std::cout << "Fetch GPS failed" << std::endl;
		}
		// 决策规划
		static int lastTargetPathIndex = -1;
		double steering = calculateSteering(route, &Gps, lastTargetPathIndex);
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelDebug, "steering: %f", steering);
		else
			std::cout << "steering:" << steering << std::endl;

		//路径规划
		if ((int(sqrtf(pow(Gps.velX, 2) + pow(Gps.velY, 2))) * 3.6)>40) {
			UtilDriver::setDriver(Gps.timestamp, 0, 0.1, steering);

		}
		else
			UtilDriver::setDriver(Gps.timestamp, 0.1, 0, steering);
		SimOneAPI::NextFrame(frame);
	}
}
