#include "SimOneNetAPI.h"
#include "SSD/SimPoint3D.h"
#include "util/UtilMath.h"
#include "utilStartSimOneNode.h"
#include "../HDMap/include/SampleGetNearMostLane.h"
#include "../HDMap/include/SampleGetLaneST.h"
#include "CloudPlatform.h"

#include <memory>
#include <limits>
#include <iostream>

//Main function
//
int main()
{

	bool inAEBState = false;
	bool isSimOneInitialized = false;
	StartSimOne::WaitSimOneIsOk(true);
	SimOneSM::SetDriverName(0, "AEB");

	int timeout = 20;
	while (true) {
		if (SimOneSM::LoadHDMap(timeout)) {
			if (CLOUD_PLATFORM)
				SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelInformation, "HDMap Information Loaded");
			else
				std::cout << "HDMap Information Loaded" << std::endl;
			break;
		}
		if (CLOUD_PLATFORM)
			SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelInformation, "HDMap Information Loading...");
		else
			std::cout << "HDMap Information Loading..." << std::endl;
	}

	while (true) {
		int frame = SimOneAPI::Wait();

		if (SimOneAPI::GetCaseRunStatus() == SimOne_Case_Status::SimOne_Case_Status_Stop) {
			break;
		}

		std::unique_ptr<SimOne_Data_Gps> pGps = std::make_unique<SimOne_Data_Gps>();
		if (!SimOneAPI::GetSimOneGps(pGps.get())) {
			if (CLOUD_PLATFORM)
				SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "Fetch GPS failed");
			else
				std::cout << "Fetch GPS failed" << std::endl;
		}
       
		std::unique_ptr<SimOne_Data_Obstacle> pObstacle = std::make_unique<SimOne_Data_Obstacle>();
		if (!SimOneAPI::GetSimOneGroundTruth(pObstacle.get())) {
			if (CLOUD_PLATFORM)
				SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelWarning, "Fetch obstacle failed");
			else
				std::cout << "Fetch obstacle failed" << std::endl;
		}
		
		if (SimOneAPI::GetCaseRunStatus() == SimOne_Case_Status::SimOne_Case_Status_Running && pObstacle->timestamp > 0 && pGps->timestamp > 0) {
			if (!isSimOneInitialized) {
				if (CLOUD_PLATFORM)
					SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelInformation, "SimOne Initialized!");
				else
					std::cout << "SimOne Initialized!" << std::endl;
				isSimOneInitialized = true;
			}

			SSD::SimPoint3D mainVehiclePos(pGps->posX, pGps->posY, pGps->posZ);
			double mainVehicleSpeed = UtilMath::calculateSpeed(pGps->velX, pGps->velY, pGps->velZ);

			double minDistance = std::numeric_limits<double>::max();
			int potentialObstacleIndex = pObstacle->obstacleSize;
			SSD::SimString mainVehicleLaneId = SampleGetNearMostLane(mainVehiclePos);
			SSD::SimString potentialObstacleLaneId = "";
			for (size_t i = 0; i < pObstacle->obstacleSize; ++i) {
				SSD::SimPoint3D obstaclePos(pObstacle->obstacle[i].posX, pObstacle->obstacle[i].posY, pObstacle->obstacle[i].posZ);
				SSD::SimString obstacleLaneId = SampleGetNearMostLane(obstaclePos);
				if (mainVehicleLaneId == obstacleLaneId) {
					double obstacleDistance = UtilMath::planarDistance(mainVehiclePos, obstaclePos);

					if (obstacleDistance < minDistance) {
						minDistance = obstacleDistance;
						potentialObstacleIndex = i;
						potentialObstacleLaneId = obstacleLaneId;
					}
				}
			}

			auto& potentialObstacle = pObstacle->obstacle[potentialObstacleIndex];
			double obstacleSpeed = UtilMath::calculateSpeed(potentialObstacle.velX, potentialObstacle.velY, potentialObstacle.velZ);


			SSD::SimPoint3D potentialObstaclePos(potentialObstacle.posX, potentialObstacle.posY, potentialObstacle.posZ);
			double sObstalce = 0;
			double tObstacle = 0;

			double sMainVehicle = 0;
			double tMainVehicle = 0;

			bool isObstalceBehind = false;
			if (!potentialObstacleLaneId.Empty()) {

				SampleGetLaneST(potentialObstacleLaneId, potentialObstaclePos, sObstalce, tObstacle);
				SampleGetLaneST(mainVehicleLaneId, mainVehiclePos, sMainVehicle, tMainVehicle);

				isObstalceBehind = sMainVehicle >= sObstalce ? false : true;
			}

			std::unique_ptr<SimOne_Data_Control> pControl = std::make_unique<SimOne_Data_Control>();

			// Control mainVehicle with SimOneDriver
			SimOneSM::GetDriverControl(0, pControl.get());

			// Control mainVehicle without SimOneDriver
			/*pControl->throttle = 0.5;
			pControl->brake = 0;
			pControl->steering = 0;
			pControl->handbrake = 0;
			pControl->isManualGear = 0;
			pControl->gear = static_cast<EGearMode>(1);*/

			if (isObstalceBehind) {
				double defaultDistance = 10.f;
				double timeToCollision = std::abs((minDistance - defaultDistance)) / (obstacleSpeed - mainVehicleSpeed);
				double defautlTimeToCollision = 3.4f;
				if (-timeToCollision < defautlTimeToCollision && timeToCollision < 0) {
					inAEBState = true;
					pControl->brake = (float)(mainVehicleSpeed * 3.6f * 0.65f + 0.20f);
				}

				if (inAEBState) {
					pControl->throttle = 0.;
				}
			}	
			SimOneSM::SetDrive(0, pControl.get());
		}
		else {
			if (CLOUD_PLATFORM)
				SimOneAPI::bridgeLogOutput(ELogLevel_Type::ELogLevelInformation, "SimOne Initializing...");
			else
				std::cout << "SimOne Initializing..." << std::endl;
		}

		SimOneAPI::NextFrame(frame);
	}
	return 0;
}
