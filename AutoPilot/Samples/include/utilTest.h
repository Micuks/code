/*************************************************************************
	> File Name: utilTest.cpp
	> Created Time: 2020年12月26日
 ************************************************************************/

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "utilStartSimOneNode.h"
#include "SimOneStreamingAPI.h"
#include "gtest/gtest.h"


class GlobalTestCallBack :public testing::Test
{
public:
	virtual void SetUp()
	{
		StartSimOne::WaitSimOneIsOk(false);
		std::cout << "already  SetUp----------------------" << std::endl;
		SimOneAPI::SetSensorPhysicalbasedDataEnable(true);
		SimOneAPI::SetSensorObjectbasedDataEnable(true);
		SimOneAPI::SetSensorOSIDataEnable(true);
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	virtual void TearDown() {
		SimOneAPI::StopSimOneNode();
		std::cout << "already  TearDown----------------------" << std::endl;
	}
};

class GlobalTestSync :public testing::Test
{
public:
	virtual void SetUp()
	{
		StartSimOne::WaitSimOneIsOk(true);
		std::cout << "already  SetUp----------------------" << std::endl;
		SimOneAPI::SetSensorPhysicalbasedDataEnable(true);
		SimOneAPI::SetSensorObjectbasedDataEnable(true);
		SimOneAPI::SetSensorOSIDataEnable(true);
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	virtual void TearDown() {
		SimOneAPI::StopSimOneNode();
		std::cout << "already  TearDown----------------------" << std::endl;
	}
};


//extern bool g_Flag_Down;
class GlobalSMTest :public testing::Test
{
public:
	int number = 0;
	int whileNumber = 0;
	virtual void SetUp()
	{
		//SimOneSM::Start();
		StartSimOne::WaitSimOneIsOk(false);
		SimOneAPI::SetSensorPhysicalbasedDataEnable(true);
		SimOneAPI::SetSensorObjectbasedDataEnable(true);
		SimOneAPI::SetSensorOSIDataEnable(true);
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		std::cout << "already  SetUp----------------------" << std::endl;
	
	}

	virtual void TearDown() {
		SimOneAPI::StopSimOneNode();
		std::cout << "already  TearDown----------------------" << std::endl;
	}
};


