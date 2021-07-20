#pragma once
#include "SimOneNetAPI.h"
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"

void GetSensorDetectionsJsonResult(int objectSize, SimOne_Data_SensorDetections_Entry *objects) {

	if (objectSize != 0)
	{
		nlohmann::json root_array;
		for (int i = 0; i < objectSize; ++i)
		{
			nlohmann::json obj;
			obj["id"] = objects[i].id;

			std::string typeString;

			switch ((int)objects[i].type) {
			case 4:
				typeString = "Pedestrian";
				break;
			case 6:
				typeString = "Car";
				break;
			case 7:
				typeString = "Static";
				break;
			case 8:
				typeString = "Bicycle";
				break;
			case 12:
				typeString = "RoadMark";
				break;
			case 13:
				typeString = "TrafficSign";
				break;
			case 15:
				typeString = "TrafficLight";
				break;
			case 17:
				typeString = "Rider";
				break;
			case 18:
				typeString = "Truck";
				break;
			case 19:
				typeString = "Bus";
				break;
			case 20:
				typeString = "SpecialVehicle";
				break;
			case 21:
				typeString = "Motorcycle";
				break;
			case 22:
				typeString = "Dynamic";
				break;
			case 26:
				typeString = "SpeedLimitSign";
				break;
			case 27:
				typeString = "BicycleStatic";
				break;
			case 29:
				typeString = "RoadObstacle";
				break;
			default:
				typeString = "Unknown";
			}

			obj["posX"] = objects[i].posX;
			obj["posY"] = objects[i].posY;
			obj["posZ"] = objects[i].posZ;
			obj["velX "] = objects[i].velX;
			obj["velY"] = objects[i].velY;
			obj["velZ"] = objects[i].velZ;
			obj["length"] = objects[i].length;
			obj["width"] = objects[i].width;
			obj["height"] = objects[i].height;

			obj["type"] = typeString;

			obj["oriX"] = objects[i].oriX;
			obj["oriY"] = objects[i].oriY;
			obj["oriZ"] = objects[i].oriZ;
			obj["probability"] = objects[i].probability;
			obj["relativePosX"] = objects[i].relativePosX;
			obj["relativePosY"] = objects[i].relativePosY;
			obj["relativePosZ"] = objects[i].relativePosZ;
			obj["relativeRotX"] = objects[i].relativeRotX;
			obj["relativeRotY"] = objects[i].relativeRotY;
			obj["relativeRotZ"] = objects[i].relativeRotZ;
			obj["relativeVelX"] = objects[i].relativeVelX;
			obj["relativeVelY"] = objects[i].relativeVelY;
			obj["relativeVelZ"] = objects[i].relativeVelZ;

			//root_array[typeString] = obj;
			root_array.push_back(obj);

		}
		std::cout << root_array.dump() << std::endl;
		exit(0);
	}

}
