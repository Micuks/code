/*!
* An sample for SimOneNetAPI based on an AVP sample (perpendicular parking)
*
* @file main.cpp
* @author YejingWang
* @version 2.0 12/24/2020
*/

#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <thread>
#include <chrono>

#include "SimOneNetAPI.h"
#include "UtilMath.hpp"
#include "UtilUnit.hpp"
#include "UtilDriver.hpp"
#include "AVPLog.hpp"
#include "AVPPlanner.hpp"

enum AVPStatus
{
	eApproaching,
	eForwarding,
	eBrakingPrep,
	eReversing,
	eFinishing,
	eWaiting,
	eLeaving,
	eEnded,
	eUnknown
};

/*!
* @function FindTargetParkingSpace
* @brief Find the target parking space
* @param
*   parkingSpaces: List of all parking spaces
@param
*   obstacles: Pointer of information of all the obstacles
* @param[out]
*   targetParkingSpace: Found target parking space
*/
void FindTargetParkingSpace(const SSD::SimVector<HDMapStandalone::MParkingSpace>& parkingSpaces,
	const SimOne_Data_Obstacle* obstacles, HDMapStandalone::MParkingSpace& targetParkingSpace)
{
	std::vector<size_t> availableParkingSpaceIndices;
	for (size_t i = 0; i < parkingSpaces.size(); ++i)
	{
		auto& parkingSpace = parkingSpaces[i];
		auto& vertices = parkingSpace.boundaryKnots;
		bool occupied = false;
		for (size_t j = 0; j < obstacles->obstacleSize; ++j)
		{
			auto& obstacle = obstacles->obstacle[j];
			SSD::SimPoint3D pos(obstacle.posX, obstacle.posY, obstacle.posZ);
			//if (inParkingSpace(pos, obstacle.theta, obstacle.length, obstacle.width, parkingSpace))
			if (UtilMath::InRectangleMargin(pos, vertices[0], vertices[2]))
			{
				std::cout << "ParkingSpace[" << i << "] occupied!" << std::endl;
				occupied = true;
				break;
			}
		}
		if (!occupied)
		{
			availableParkingSpaceIndices.push_back(i);
		}
	}
	std::cout << std::endl;

	// choose the first available 
	targetParkingSpace = parkingSpaces[availableParkingSpaceIndices[0]];
}

/*!
* @function RearrangeKnots
* @brief Rearrange boundary knots of the parking space so that they start from its top left knot
* @param
*   space: Interested parking space
*/
void RearrangeKnots(HDMapStandalone::MParkingSpace& space)
{
	size_t knotSize = space.boundaryKnots.size();
	SSD::SimPoint2D heading{ space.heading.x, space.heading.y };
	SSD::SimPoint3DVector arrangedBoundaryKnots(knotSize);
	double headingErrorThresholdDegree = 10.;
	for (size_t i = 0; i < knotSize; ++i)
	{
		SSD::SimPoint2D dir = { space.boundaryKnots[i + 1].x - space.boundaryKnots[i].x,
								space.boundaryKnots[i + 1].y - space.boundaryKnots[i].y };
		double angle = UtilMath::Angle(heading, dir);
		if (angle > 0. && angle < UtilUnit::DegreeToRad(headingErrorThresholdDegree))
		{
			for (size_t j = 0; j < knotSize; ++j)
			{
				size_t index = i + j + 2 < knotSize ? i + j + 2 : i + j + 2 - knotSize;
				arrangedBoundaryKnots[j] = space.boundaryKnots[index];
			}
			break;
		}
	}
	for (size_t i = 0; i < knotSize; ++i)
	{
		space.boundaryKnots[i] = arrangedBoundaryKnots[i];
	}
}

/*!
* @function InParkingSpace
* @brief Determine if a vehicle is inside a parking space
* @param
*   pos: Position of the vehicle (its rear center)
* @param
*   theta: Heading of the vehicle in radians
* @param
*   length: Length of the vehicle
* @param
*   width: Width of the vehicle
* @param
*   space: Interested parking space
* @return
*   True if any of the vehicle's vertices is inside the parking space; false otherwise
*/
bool InParkingSpace(const SSD::SimPoint3D& pos, const double theta, const double length, const double width, const HDMapStandalone::MParkingSpace& space)
{
	SSD::SimPoint3D p1(pos.x + width / 2. * cos(theta) + length / 2. * sin(theta),
		pos.y + width / 2. * sin(theta) - length / 2. * cos(theta), pos.z);
	SSD::SimPoint3D p2(pos.x + width / 2. * cos(theta) - length / 2. * sin(theta),
		pos.y + width / 2. * sin(theta) + length / 2. * cos(theta), pos.z);
	SSD::SimPoint3D p3(pos.x - width / 2. * cos(theta) - length / 2. * sin(theta),
		pos.y - width / 2. * sin(theta) + length / 2. * cos(theta), pos.z);
	SSD::SimPoint3D p4(pos.x - width / 2. * cos(theta) + length / 2. * sin(theta),
		pos.y - width / 2. * sin(theta) - length / 2. * cos(theta), pos.z);

	return UtilMath::InRectangleMargin(p1, space.boundaryKnots[0], space.boundaryKnots[2]) || UtilMath::InRectangleMargin(p2, space.boundaryKnots[0], space.boundaryKnots[2]) ||
		UtilMath::InRectangleMargin(p3, space.boundaryKnots[0], space.boundaryKnots[2]) || UtilMath::InRectangleMargin(p4, space.boundaryKnots[0], space.boundaryKnots[2]);
}

int main(int argc, char* argv[])
{
	std::unique_ptr<SimOne_Data_Gps> gpsPtr = std::make_unique<SimOne_Data_Gps>();
	std::unique_ptr<SimOne_Data_Obstacle> obstaclesPtr = std::make_unique<SimOne_Data_Obstacle>();
	std::unique_ptr<SimOne_Data_WayPoints> wayPointsPtr = std::make_unique<SimOne_Data_WayPoints>();

	bool leaveAfterParked = true;

	/* 1. Initialize */
	while (!SimOneSM::Start())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	int timeoutSecond = 20;
	if (!SimOneSM::LoadHDMap(timeoutSecond))
	{
		std::cout << "Failed to load map!" << std::endl;
		return 0;
	}

	SSD::SimPoint3D startPoint;
	if (SimOneSM::GetGps(0, gpsPtr.get()))
	{
		startPoint.x = gpsPtr->posX;
		startPoint.y = gpsPtr->posY;
		startPoint.z = gpsPtr->posZ;
	}
	else
	{
		std::cout << "Fetch GPS failed" << std::endl;
	}


	/* 2. Get parking spaces */
	SSD::SimVector<HDMapStandalone::MParkingSpace> parkingSpaces;
	SimOneSM::GetParkingSpaceList(parkingSpaces);

	for (size_t i = 0; i < parkingSpaces.size(); ++i)
	{
		auto& parkingSpace = parkingSpaces[i];
		auto& vertices = parkingSpace.boundaryKnots;
		std::cout << "ParkingSpace[" << i << "]: " << std::endl;
		for (size_t j = 0; j < 4; ++j)
		{
			std::cout << "[" << vertices[j].x << ", " << vertices[j].y << "]" << std::endl;
		}
	}
	std::cout << std::endl;


	/* 3. Get obstacles */
	SimOneSM::GetGroundTruth(0, obstaclesPtr.get());
	for (size_t i = 0; i < obstaclesPtr->obstacleSize; ++i)
	{
		std::cout << "Obstacles[" << i << "]: " << std::endl;
		auto& obstacle = obstaclesPtr->obstacle[i];
		std::cout << "[" << obstacle.posX << ", " << obstacle.posY << "]" <<std::endl;
	}
	std::cout << std::endl;


	/* 4. Determine target parking space */
	HDMapStandalone::MParkingSpace targetParkingSpace;
	FindTargetParkingSpace(parkingSpaces, obstaclesPtr.get(), targetParkingSpace);

	// rearrange boundaryKnots of the target parking space
	RearrangeKnots(targetParkingSpace);
	std::cout << "Rearranged parking space:" << std::endl;

	for (size_t i = 0; i < targetParkingSpace.boundaryKnots.size(); ++i)
	{
		std::cout << "[" << targetParkingSpace.boundaryKnots[i].x << ", " << targetParkingSpace.boundaryKnots[i].y << "]" << std::endl;
#if AVP_LOG
		AVPLog::getInstance().addData(targetParkingSpace.boundaryKnots[i].x);
		AVPLog::getInstance().addData(targetParkingSpace.boundaryKnots[i].y);
#endif // AVP_LOG
	}
	std::cout << std::endl;
#if AVP_LOG
	AVPLog::getInstance().addNewLine();
#endif // AVP_LOG


	/* 5. Get terminal point */
	while (!SimOneSM::GetWayPoints(wayPointsPtr.get()))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	auto lastWayPoint = wayPointsPtr->wayPoints[wayPointsPtr->wayPointsSize - 1];
	SSD::SimPoint3D terminalPoint{ lastWayPoint.posX, lastWayPoint.posY, 0. };

	/* 6. Plan */
	VehicleParam veh;
	veh.Lr = 0.88;
	veh.Lf = 1.;
	veh.L = 2.9187;

	AVPPlanner planner(targetParkingSpace, startPoint, terminalPoint, veh, leaveAfterParked);
	planner.plan();

	/* 6. Join sync and control */
	SimOneAPI::StartSimOneNode(0, 0);
	SimOneAPI::SubMainVehicle(0,true);

	AVPStatus status = AVPStatus::eForwarding;

	bool brakingPrepStarted = false;
	bool reversingStarted = false;
	bool finishingStarted = false;
	bool waitingStarted = false;
	double brakingPrepTime = 1.;
	double waitingTimeSecond = 3.;
	auto startTime = std::chrono::system_clock::now();
	double headingErrorThresholdDegree = 1.;
	double parkingEndDistanceThreshold = 0.5;
	double leavingEndDistanceThreshold = 0.5;

	while (1)
	{
		int frame = SimOneAPI::Wait();

		if (!SimOneSM::GetGps(0, gpsPtr.get()))
		{
			std::cout << "Fetch GPS failed" << std::endl;;
		}

#if AVP_LOG
		AVPLog::getInstance().addData(gpsPtr->posX);
		AVPLog::getInstance().addData(gpsPtr->posY);
#endif // AVP_LOG

		if (status == AVPStatus::eForwarding) // approaching the parking space
		{
			if (UtilMath::PlanarDistance({ gpsPtr->posX, gpsPtr->posY, gpsPtr->posZ }, planner.ForwardTrajectory().back()) < 0.05)
			{
				UtilDriver::SetControl(gpsPtr->timestamp, 0., 1., 0., EGearMode_Neutral);
				status = AVPStatus::eBrakingPrep;
				std::cout << "Reached reverse point!" << std::endl;
			}
			else {
				double steering = UtilDriver::CalculateSteering(planner.ForwardTrajectory(), gpsPtr.get());
				UtilDriver::SetControl(gpsPtr->timestamp, 0.05, 0., steering);
			}
		}
		else if (status == AVPStatus::eBrakingPrep) // coming to a full stop
		{
			if (!brakingPrepStarted)
			{
				startTime = std::chrono::system_clock::now();
				brakingPrepStarted = true;
			}
			else
			{
				// wait for a total of 1 second
				std::chrono::duration<double> currentBrakingPrepTime = std::chrono::system_clock::now() - startTime;
				if (currentBrakingPrepTime.count() > brakingPrepTime)
				{
					status = AVPStatus::eReversing;
				}
			}
			UtilDriver::SetControl(gpsPtr->timestamp, 0., 1., 0., EGearMode_Neutral);
		}
		else if (status == AVPStatus::eReversing) // reversing towards the parking space
		{
			if (UtilMath::CloseEnough(std::atan2(targetParkingSpace.heading.y, targetParkingSpace.heading.x),
				(double)gpsPtr->oriZ, UtilUnit::DegreeToRad(headingErrorThresholdDegree)))
			{
				status = AVPStatus::eFinishing;
				std::cout << "Start reversing straightly!" << std::endl;
			}
			else
			{
				double speedKmH = UtilUnit::MsToKmH(UtilMath::Length({ gpsPtr->velX, gpsPtr->velY, gpsPtr->velZ }));
				double throttle, brake;
				if (speedKmH < 3 && !reversingStarted)
				{
					throttle = 0.03f;
					brake = 0.f;
				}
				else
				{
					reversingStarted = true;
					throttle = 0.f;
					brake = 0.02f;
				}
				double steering = UtilDriver::CalculateSteering(planner.ReverseTrajectory(), gpsPtr.get());
				UtilDriver::SetControl(gpsPtr->timestamp, throttle, brake, steering, EGearMode_Reverse);
			}
		}
		else if (status == AVPStatus::eFinishing) // finishing
		{
			double endDistance = UtilMath::Distance({ gpsPtr->posX, gpsPtr->posY }, planner.ParkingEndPoint());
			if (endDistance < parkingEndDistanceThreshold)
			{
				std::cout << "Finished parking!" << std::endl;
				UtilDriver::SetControl(gpsPtr->timestamp, 0., 1., 0., EGearMode_Neutral);
				if (leaveAfterParked)
				{
					status = AVPStatus::eWaiting;
				}
				else
				{
					status = AVPStatus::eEnded;
					break;
				}
			}
			// let the vehicle slide
			UtilDriver::SetControl(gpsPtr->timestamp, 0., 0., 0., EGearMode_Reverse);
		}
		else if (status == AVPStatus::eWaiting)
		{
			if (!waitingStarted)
			{
				startTime = std::chrono::system_clock::now();
				waitingStarted = true;
			}
			else
			{
				// wait for a total of waitingTimeSecond
				std::chrono::duration<double> currentWaitingTimeSecond = std::chrono::system_clock::now() - startTime;
				if (currentWaitingTimeSecond.count() > waitingTimeSecond)
				{
					status = AVPStatus::eLeaving;
					std::cout << "Finished waiting for " << waitingTimeSecond << " second!" << std::endl;
				}
			}
			UtilDriver::SetControl(gpsPtr->timestamp, 0., 1., 0., EGearMode_Neutral);
		}
		else if (status == AVPStatus::eLeaving)
		{
			double endDistance = UtilMath::PlanarDistance({ gpsPtr->posX, gpsPtr->posY, 0. }, planner.LeavingTrajectory().back());
			if (endDistance < leavingEndDistanceThreshold)
			{
				status = AVPStatus::eEnded;
				std::cout << "Finished leaving!" << std::endl;
				UtilDriver::SetControl(gpsPtr->timestamp, 0., 1., 0., EGearMode_Neutral);
			}
			else
			{
				double steering = UtilDriver::CalculateSteering(planner.LeavingTrajectory(), gpsPtr.get());
				UtilDriver::SetControl(gpsPtr->timestamp, 0.05, 0., steering);
			}
		}

		SimOneAPI::NextFrame(frame);
	}

	return 0;
}
