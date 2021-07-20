#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <iostream>
#include <memory>

#include "SimOneNetAPI.h"
#include "SimOneIOStruct.h"

using namespace std;

class UtilDriver
{
public:
	static void setDriver(long long& timestamp, const float& throttle, const float& brake, const float& steering)
	{
		std::unique_ptr<SimOne_Data_Control> pControl = std::make_unique<SimOne_Data_Control>();
		pControl->timestamp = timestamp;
		pControl->throttle = throttle;
		pControl->brake = brake;
		pControl->steering = steering;
		pControl->handbrake = 0;
		pControl->isManualGear = 0;
		pControl->gear = static_cast<EGearMode>(1);
		SimOneSM::SetDrive(0, pControl.get());
	}
	
	static double calculateSteering(const SSD::SimPoint3DVector& targetPath, SimOne_Data_Gps *pGps)
	{
		std::vector<float> pts;
		for (size_t i = 0; i < targetPath.size(); ++i)
		{
			pts.push_back(pow((pGps->posX - targetPath[i].x), 2) + pow((pGps->posY - targetPath[i].y), 2));
		}

		size_t index = min_element(pts.begin(), pts.end()) - pts.begin();
		size_t forwardIndex = 0;
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
};
