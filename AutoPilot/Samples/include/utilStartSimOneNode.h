/*************************************************************************
    > File Name: utilStartSimOneNode.cpp
    > Created Time: 2020年12月18日 
 ************************************************************************/

#include <iostream>
#include <vector>
#include <thread>
#include <stdio.h>
#include <string.h>
#include "SimOneNetAPI.h"

SimOne_Data_MainVehicle_Status mainVehicleStatus;
SimOne_Data_MainVehicle_Info MainVehicleInfo;
class StartSimOne
{
public:
	static void WaitSimOneIsOk(bool isJoinTimeLoop) {
		//连接BridgeIO，允许加入帧同步true
		//SimOneAPI::SetServerInfo("10.2.35.159", 23789);
		SimOneAPI::StartSimOneNode(0, 0);
		SimOneAPI::SimOneNodeReady();
		
		//获取案例状态
		while (true) {
			if (SimOneAPI::GetCaseRunStatus() == SimOne_Case_Status::SimOne_Case_Status_Running) {
				break;
			}
		}

		//获取主车列表信息
		while (true) {
			SimOneAPI::GetMainVehicleList(&MainVehicleInfo);
			if (int(MainVehicleInfo.size) > 0) {
				std::cout << "MainVehicle Initialized" << std::endl;
				std::cout << "pMainVehicleInfo size:" << MainVehicleInfo.size << std::endl;
				break;
			}
			else {
				std::cout << "MainVehicle Initializing..." << std::endl;
			}
		}

		int count = 0;
		while (true)
		{
			//订阅id为0的主车，主车id范围0-9
			bool bRet = SimOneAPI::SubMainVehicle(0, isJoinTimeLoop);
			if (!bRet) {
				std::cout << "failed to subscribe mian vehicle" << std::endl;
				count++;
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				continue;
			}
			break;
		}

		while (true)
		{
			//当主车状态大于0时，SimOne环境已经准备完毕，可以进行api调用
			bool bRet = SimOneAPI::GetMainVehicleStatus(&mainVehicleStatus);
			if (!bRet) {
				getchar();
			}
			if (mainVehicleStatus.mainVehicleId == 0 && mainVehicleStatus.mainVehicleStatus > 0) {
				std::cout << "MainVehicle is ready" << std::endl;
				break;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
};

