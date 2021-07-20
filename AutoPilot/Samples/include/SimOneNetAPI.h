/*!
	@file SimOneSMAPI.hpp
	@author Huiyong.Men 2019/11/11
	@brief This is an API for SIM-ONE, used to communicateing with CybertronBridgeSM by shared memory.
*/
#pragma once

#ifdef BUILD_SIMONE_IO
#if defined(WIN32) || defined(_WIN32)
#define SIMONE_NET_API __declspec(dllexport)
#elif defined(__linux__) || defined(__linux)
#define SIMONE_NET_API __attribute__((visibility("default")))
#endif
#else
#define SIMONE_NET_API
#endif

#include <string>
#include "SimOneIOStruct.h"
#ifndef WITHOUT_HDMAP
#include "public/common/MEnum.h"
#include "public/common/MLaneLink.h"
#include "public/common/MLaneInfo.h"
#include "public/common/MRoadMark.h"
#include "public/common/MSignal.h"
#include "public/common/MObject.h"
#include "public/common/MParkingSpace.h"
#include "SSD/SimPoint3D.h"
#endif

//namespace HDMapStandalone
//{
//    struct MLaneInfo;
//	struct MLaneLink;
//}

#ifdef __cplusplus
extern "C"
{
#endif
	//SimOneAPI命名空间是新的API,SimOneSM是老的命名空间为了兼容以前的接口
	namespace SimOneAPI{
		/*
			Author:mnq
			本套仿真API，支持从热区获取数据，也支持获取传感数据，以下是一些注意事项
			1：一个dll实例只允许订阅一个主车，目前不支持一个DLL支持多个主车的需求，如果要订阅多个主车，请启用多个进程
			调用多个dll实例
			2：StartSimOneNode目前传入订阅主车的ID
			3：本系统支持帧同步方式获取数据，和非帧同步方式获取数据
		*/

		/*!
		获取当前库的版本号
		\li function:
		*	GetVersion
		\li brief:
		*	Get the version number of the current library
		@param
		*	None
		@return
		*	version number
		*/
		SIMONE_NET_API const char* GetVersion();
		SIMONE_NET_API bool SendRouteMessageToWeb(int length, void* pBuffer, int msgId);
		SIMONE_NET_API bool SendRouteMessage(int length, void* pBuffer, int msgId, int toNodeId, SimOne_ClientType toNodeType);
		SIMONE_NET_API bool ReceiveRouteMessageCB(void(*cb)(int fromId, SimOne_ClientType fromType,int length, const void* pBuffer, int commandId));
		/*!
		设置性能测试文件参数
		\li function:
		*	SetupPerformance
		\li brief:
		*	Set performance test file parameters
		@param
		*	isOpen:true/false write performance test file,intervalPacketCount:Interval number of packets,filePath:file path
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetupPerformance(bool isOpen =false , int intervalPacketCount = 200, char* filePath = 0);
		/*!
		日志设置接口
		\li function:
		*	SetupLogLevel
		\li brief:
		*	Set log interface
		@param
		*	level:warning,error,info flag:true/false
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool bridgeLogOutput(ELogLevel_Type level, const char *format, ...);
		/*!
		设置服务的地址和端口号
		\li function:
		*	SetServerInfo
		\li brief:
		*	Set the address and port number of the service
		@param
		*	serverIP:set connection bridgeio of IP address,port:set connection bridgeio of IP port
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetServerInfo(const char *serverIP = "127.0.0.1", int port = 23789);
		/*!
		StartSimOneNode 启动node，输入主车ID，一个主车ID，只能去连一次birdgeIO,如果当前主车ID被占用了，会报错
		\li function:
		*	StartSimOneNode
		\li brief:
		*	Get the version number of the current library
		@param
		*	startCase: case start callback,endCase: case end callback,registerNodeId:connect bridgeIO node id
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool StartSimOneNode(void(*startCase)(), void(*endCase)(), int registerNodeId = 0);
		/*!
		停止API node
		\li function:
		*	GetVersion
		\li brief:
		*	Stop SimOne API node
		@param
		*	None
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool StopSimOneNode();
		/*!
		通知simone内部系统已经准备好
		\li function:
		*	SimOneNodeReady
		\li brief:
		*	Inform Simone that the internal system is ready
		@param
		*	None
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SimOneNodeReady();
		/*!
		获取案例详情
		\li function:
		*	GetCaseInfo
		\li brief:
		*	Get case information
		@param[out]
		*	pCaseInfo:caseName,caseId,taskId,sessionId
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetCaseInfo(SimOne_Data_CaseInfo *pCaseInfo);
		/*!
		获取案例运行情况（运行中，停止）
		\li function:
		*	GetCaseRunStatus
		\li brief:
		*	Get case running status
		@param
		*	None
		@return
		*	Stop,Running
		*/
		SIMONE_NET_API SimOne_Case_Status GetCaseRunStatus();
		/*!
		获取主车信息列表，只需要获取一次
		\li function:
		*	GetMainVehicleList
		\li brief:
		*	Get the main vehicle information list
		@param[out]
		*	pMainVehicleInfo:mainvehicle id/num/type data(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetMainVehicleList(SimOne_Data_MainVehicle_Info *pMainVehicleInfo);
		/*!
		订阅主车
		\li function:
		*	SubMainVehicle
		\li brief:
		*	Subscribe to mainVehicle
		@param
		*	mainVehicleId:id,isJoinTimeLoop:true/false join frame synchronization
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SubMainVehicle(int mainVehicleId, bool isJoinTimeLoop );
		/*!
		获取主车状态信息
		\li function:
		*	GetMainVehicleStatus
		\li brief:
		*	Get the status information of mainvehicle
		@param
		*	pMainVehicleStatus[out]:id,status
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetMainVehicleStatus(SimOne_Data_MainVehicle_Status *pMainVehicleStatus);
		/*!
		获取主车状态信息回调
		\li function:
		*	SetMainVehicleStatusCB
		\li brief:
		*	Get the status information of mainvehicle callback
		@param
		*	cb: VehicleStatus data fetch callback function
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetMainVehicleStatusCB(void(*cb)(SimOne_Data_MainVehicle_Status *pMainVehicleStatus));

		/*两种工作的方式
			1:加入帧同步
			2:不加入帧同步获取
		*/
		/*!
			第一种方式：加入帧同步
			时间推进接口，没调用一次，时间会往前推进一帧
			配合其他热区数据的接口一起使用
			加入帧同步的代码流程
			isJoinTimeLoop = true
			SetServerInfo("127.0.0.1",23789)
			StartSimOneNode(0,0)
			GetCaseRunStatus()
			SubMainVehicle(0,isJoinTimeLoop)
			while(true){
						int frame = Wait()
						GetGps()
						GetTrafficLight()
						GetPrediction()
						GetObstacleData()
						NextFrame(frame)
			}

		*/
		/*!
		获取当前帧值
		\li function:
		*	Wait
		\li brief:
		*	Get the current frame value
		@param
		*   None
		@return
		*	frame value
		*/
		SIMONE_NET_API int Wait();
		/*!
		进行下一帧
		\li function:
		*	NextFrame
		\li brief:
		*	Go to the next frame
		@param
		*   frame: current frame value
		@return
		*	None
		*/
		SIMONE_NET_API void NextFrame(int frame);
		/*!
		获取主车GPS信息
		\li function:
		*	GetSimOneGps
		\li brief:
		*	Get main vehicle GPS
		@param[out]
		*   pGps: GPS data(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetSimOneGps(SimOne_Data_Gps *pGps);

        /*!
        注册SimOne_Data_Gps包含的状态以外的主车状态信息
        \li function:
        *	RegisterSimOneVehicleState
        \li brief:
        *	Register states of main vehicle dynamics 
        @param[pStateIndics]
        *   pStateIndics: array of state names
        @param[size]
        *   size: state number in pStateIndics
        @return
        *	Success or not
        */
        SIMONE_NET_API bool RegisterSimOneVehicleState(SimOne_Data_Vehicle_State *pStateIndics, int size);

        /*!
        获取通过RegisterSimOneVehicleState注册的主车状态信息
        \li function:
        *	GetSimOneVehicleState
        \li brief:
        *	Get states of main vehicle dynamics which are registered by RegisterSimOneVehicleState
        @param[pVehExtraState]
        *   pVehExtraState: states of main vehicle dynamics
        @return
        *	Success or not
        */
        SIMONE_NET_API bool GetSimOneVehicleState(SimOne_Data_Vehicle_Extra* pVehExtraState);

		/*!
		得到仿真场景中的物体的真值
		\li function:
		*	GetSimOneGroundTruth
		\li brief:
		*	Get Ground Truth Data of Objects(Obstacles) from simulation scene.
		@param[out]
		*   pObstacle: Obstacle data(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetSimOneGroundTruth(SimOne_Data_Obstacle *pObstacle);
		/*!
		仿真场景中每帧的回调,每帧开始和结束时调用回调函数
		\li function:
		*	SetFrameCB
		\li brief:
		*	The callback function is called at the beginning and end of each frame.
		@param
		*   FrameStart:Callback function at the beginning of the frame FrameEnd:Callback function at the end of the frame
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetFrameCB(void(*FrameStart)(int frame), void(*FrameEnd)(int frame));
		/*!
		主车GPS更新回调
		\li function:
		*	SetSimOneGpsCB
		\li brief:
		*	Add main vehicle GPS update callback
		@param[in]
		*   cb: GPS data update callback function
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetSimOneGpsCB(void(*cb)(SimOne_Data_Gps *pGps));
		/*!
		得到仿真场景中的物体的真值的更新回调
		\li function:
		*	SetSimOneGroundTruthCB
		\li brief:
		*	Add main vehicle obstacle update callback
		@param[in]
		*   cb: Obstacle data fetch callback function
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetSimOneGroundTruthCB(void(*cb)( SimOne_Data_Obstacle *pObstacle));

		/*!
		设置是否允许收发物理级数据
		\li function:
		*	SetSensorPhysicalbasedDataEnable
		\li brief:
		*	Set the sensor data to receive data level
		@param
		*   enable: true:receive physical data, false:do not receive physical data
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetSensorPhysicalbasedDataEnable(bool enable);
	    /*!
		设置是否允许收发目标级数据
		\li function:
		*	SetSensorObjectbasedDataEnable
		\li brief:
		*	Set the sensor data to receive data level
		@param
		*   enable: true:receive object data, false:do not receive object data
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetSensorObjectbasedDataEnable(bool enable);
		/*!
		设置是否允许收OSI数据
		\li function:
		*	SetSensorOSIDataEnable
		\li brief:
		*	Set the sensor data to receive data level
		@param
		*   enable: true:receive osi data, false:do not receive osi data
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetSensorOSIDataEnable(bool enable);
	}
	namespace SimOneSM {
		/*!
		启动SimOneAPI，允许HDmap函数和所有回调
		\li function:
		* Start
		\li brief:
		*	Start SimOneAPI, enable HDmap functions and all callbacks
		@param
		*   None
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool Start();
		/*!
		  启动SimOne OSI_API
		  \li function:
		  * Start
		  \li brief:
		  *        Start SimOne OSI_API
		  @param
		  *   None
		  @return
		  *        Success or not
		*/
		SIMONE_NET_API bool OSIStart();
		/*!
		设置主车位置
		\li function:
		*	SetPose
		\li brief:
		*	Set main vehicle pose
		@param
		*   mainVehicleId: Vehilcle index, configure order of web UI, starts from 0
		@param[in]
		*   pPose: Pose to set(input)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetPose(int mainVehicleId, SimOne_Data_Pose_Control *pPose);

		/*!
		主车控制
		\li function:
		*	SetDrive
		\li brief:
		*	Set vehicle drive control
		@param
		*   mainVehicleId: Vehilcle index, configure order of web UI, starts from 0
		@param[in]
		*   pControl: vehicle control data(input)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetDrive(int mainVehicleId, SimOne_Data_Control *pControl);	

        /*!
        主车控制
        \li function:
        *	SetDrive by planning trajectory. Not to use with SetDrive at the same time
        \li brief:
        *	Set vehicle drive control by planning trajectory
        @param
        *   mainVehicleId: Vehilcle index, configure order of web UI, starts from 0
        @param[in]
        *   pControlTrajectory: vehicle planning trajectory (input)
        @return
        *	Success or not
        */
        SIMONE_NET_API bool SetDriveTrajectory(int mainVehicleId, SimOne_Data_Control_Trajectory *pControlTrajectory);

        /*!
        设置主车控制器的名字
        \li function:
        *	SetDriverName
        \li brief:
        *	Set vehicle driver's name
        @param
        *   mainVehicleId: Vehilcle index, configure order of web UI, starts from 0
        @param[in]
        *   name: vehicle driver name, max length is 8
        */
        SIMONE_NET_API void SetDriverName(int mainVehicleId, const char* name);

		/*!
		主车ESP控制
		\li function:
		*	SetESPDrive
		\li brief:
		*	Set vehicle ESP drive control
		@param
		*   mainVehicleId: Vehicle index, configuration order from scenario editing, starting from 0
		@param[in]
		*   pESPControl: vehicle ESP control data(input)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetESPDrive(int mainVehicleId, SimOne_Data_ESP_Control *pESPControl);

		/*!
		设置主车预警消息
		\li function:
		*	SetVehicleEvent
		\li brief:
		*	Set vehicle event information
		@param
		*   mainVehicleId: Vehicle index, configuration order from scenario editing, starting from 0
		@param[in]
		*   pVehicleEvent: vehicle event information data(input)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetVehicleEvent(int mainVehicleId, SimOne_Data_Vehicle_EventInfo *pEvent);

		/*!
		预测轨迹设置
		\li function:
		*	SetTrajectory
		\li brief:
		*	Set vehicle waypoints
		@param
		*   mainVehicleId: Vehicle index, configuration order from scenario editing, starting from 0
		@param[in]
		*   pTrajectory: vehicle trajectory data(input)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetTrajectory(int mainVehicleId, SimOne_Data_Trajectory *Trajectory);

		/*!
		获取主车GPS信息
		\li function:
		*	GetGps
		\li brief:
		*	Get main vehicle GPS
		@param
		*   mainVehicleId: Vehilcle index, configure order of web UI, starts from 0
		@param[out]
		*   pGps: GPS data(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetGps(int mainVehicleId, SimOne_Data_Gps *pGps);

		/*!
		主车GPS更新回调
		\li function:
		*	SetGpsUpdateCB
		\li brief:
		*	Add main vehicle GPS update callback
		@param
		*   mainVehicleId: Vehilcle index, configure order of web UI, starts from 0
		@param[in]
		*   cb: GPS data update callback function
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetGpsUpdateCB(void(*cb)(int mainVehicleId, SimOne_Data_Gps *pGps));

		/*!
		得到仿真场景中的交通灯的真值
		\li function:
		*	GetTrafficLight
		\li brief:
		*	Get traffic lights Data of Objects(light) from simulation scene.
		@param
		*   mainVehicleId: Vehicle index, configure order of web UI, starts from 0
		@param[out]
		*   pTrafficLights: light data(output)
		@return
		*	Success or not
		*/

		SIMONE_NET_API bool GetTrafficLight(int mainVehicleId, int opendriveLightId, SimOne_Data_TrafficLight* pTrafficLight);
		
		//SIMONE_NET_API bool GetTrafficLight(int mainVehicleId, SimOne_Data_TrafficLights *pTrafficLight);
		//SIMONE_NET_API bool SetTrafficLightUpdateCB(void(*cb)(int mainVehicleId, SimOne_Data_TrafficLights *pTrafficLight));

		/*!
		得到仿真场景中的物体的真值
		\li function:
		*	GetGroundTruth
		\li brief:
		*	Get Ground Truth Data of Objects(Obstacles) from simulation scene.
		@param
		*   mainVehicleId: Vehicle index, configure order of web UI, starts from 0
		@param[out]
		*   pObstacle: Obstacle data(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetGroundTruth(int mainVehicleId, SimOne_Data_Obstacle *pObstacle);

		/*!
		得到仿真场景中的物体的真值的更新回调
		\li function:
		*	SetObstacleUpdateCB
		\li brief:
		*	Add main vehicle obstacle update callback
		@param
		*   mainVehicleId: Vehicle index, configure order of web UI, starts from 0
		@param[in]
		*   cb: Obstacle data fetch callback function
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetGroundTruthUpdateCB(void(*cb)(int mainVehicleId, SimOne_Data_Obstacle *pObstacle));

		/*!
		得到图像信息
		\li function:
		*	GetImage
		\li brief:
		*	Get Image Data
		@param
		*	mainVehicleId: Vehicle index, configure order of web UI, starts from 0
		@param
		*   sensorId: Sensor Index
		@param
		*	pImage: Image data(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetImage(const int mainVehicleId, const int sensorId, SimOne_Data_Image *pImage);

		/*!
		图像传感器回调
		\li function:
		*	SetObstacleUpdateCB
		\li brief:
		*	Image sensor update callback
		@param
		*   mainVehicleId: Vehilcle index, configure order of web UI, starts from 0
		@param[in]
		*   cb: Image data update callback function
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetImageUpdateCB(void(*cb)(int mainVehicleId, int sensorId, SimOne_Data_Image *pImage));
		/*!
		得到点云数据
		\li function:
		*	GetPointCloud
		\li brief:
		*	Get PointCloud Data
		@param
		*	mainVehicleId: Vehicle index, configure order of web UI, starts from 0
		@param[out]
		*	pPointcloud: PointCloud data(ouput)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetPointCloud(int mainVehicleId, int sensorId, SimOne_Data_Point_Cloud *pPointcloud);
		/*!
		点云数据更新回调
		\li function:
		*	SetPointCloudUpdateCB
		\li brief:
		*	PointCloud update callback
		@param
		*   mainVehicleId: Vehilcle index, configure order of web UI, starts from 0
		@param[in]
		*   cb: PointCloud data update callback function
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetPointCloudUpdateCB(void(*cb)(int mainVehicleId, int sensorId, SimOne_Data_Point_Cloud *pPointcloud));
		/*!
		得到毫米波雷达目标信息
		\li function:
		*	GetRadarDetections
		\li brief:
		*	Get millimeter wave radar detections.
		@param
		*	mainVehicleId: Vehicle index, configure order of web UI, starts from 0
		@param
		*   sensorId: Sensor Index
		@param
		*	pDetections: Radar detections(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetRadarDetections(const int mainVehicleId, const int sensorId, SimOne_Data_RadarDetection *pDetections);

		/*!
		毫米波雷达目标信息回调
		\li function:
		*	SetRadarDetectionsUpdateCB
		\li brief:
		*	Millimeter wave radar detections update callback
		@param
		*   mainVehicleId: Vehicle index, configure order of web UI, starts from 0
		@param[in]
		*   cb: Radar detections update callback function
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetRadarDetectionsUpdateCB(void(*cb)(int mainVehicleId, int sensorId, SimOne_Data_RadarDetection *pDetections));

		/*
		获得一个超声波雷达信息
		\li function:
		*	GetUltrasonicRadar
		\li brief:
		*	Get UltrasonicRadar imformations
		@param
		*   mainVehicleId: Vehicle index, configure order of web UI, starts from 0
		@param[out]
		*   pUltrasonic: ultrasonic data in SimOne_Data_UltrasonicRadar format(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetUltrasonicRadar(int mainVehicleId, int sensorId, SimOne_Data_UltrasonicRadar *pUltrasonic);
		/*
		获得所有超声波雷达信息
		\li function:
		*	GetUltrasonicRadars
		\li brief:
		*	Get UltrasonicRadars imfomations
		@param
		*   mainVehicleId: Vehicle index, configure order of web UI, starts from 0
		@param[out]
		*   pUltrasonics: ultrasonics data in SimOne_Data_UltrasonicRadars format(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetUltrasonicRadars(int mainVehicleId, SimOne_Data_UltrasonicRadars *pUltrasonics);
		/*!
		超生波雷达真值信息更新回调
		\li function:
		*	SetUltrasonicRadarsCB
		\li brief:
		*	Set ultrasonics update callback in UltrasonicRadars_data
		@param
		*   mainVehicleId: Vehilcle index, configure order of web UI, starts from 0
		@param[in]
		*   cb: Ultrasonics data update callback function
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetUltrasonicRadarsCB(void(*cb)(int mainVehicleId, SimOne_Data_UltrasonicRadars *pUltrasonics));

		/*!
		获取传感器检测到物体的对应真值
		\li function:
		*	GetSensorDetections

		\li brief:
		*	Get Ground Truth objects for current sensor, support camera, lidar and perfect perception sensors.
		@param
		*   mainVehicleId: Vehicle index, configure order of web UI, starts from 0
		@param[out]
		*   pGroundtruth: SimOne_Data_SensorDetections data(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetSensorDetections(int mainVehicleId, int sensorId, SimOne_Data_SensorDetections *pGroundtruth);

		/*!
			传感器真值信息更新回调
			\li function:
			*	SetSensorDetectionsUpdateCB
			\li brief:
			*	Set GroundTruth update callback for current sensor, support camera, lidar and perfect perception sensors.
			@param
			*   mainVehicleId: Vehicle index, configure order of web UI, starts from 0
			@param[in]
			*   cb: Groundtruth data fetch callback function
			@return
			*	Success or not
			*/
		SIMONE_NET_API bool SetSensorDetectionsUpdateCB(void(*cb)(int mainVehicleId, int sensorId, SimOne_Data_SensorDetections *pGroundtruth));

		/*!
		获取传感器检测到车道与车道线数据
		\li function:
		*	GetCameraSensorLaneInfo

		\li brief:
		*	Get LaneInfo for current sensor, support camera sensor
		@param
		*   mainVehicleId: Vehicle index, configure order of web UI, starts from 0
		@param[out]
		*   pLaneInfo: SimOne_Data_LaneInfo data(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetCameraSensorLaneInfo(int mainVehicleId, int sensorId, SimOne_Data_LaneInfo *pLaneInfo);

		/*!
		获取传感器检测到车道与车道线数据
		\li function:
		*	SetCameraSensorLaneInfoCB

		\li brief:
		*	Set LaneInfo for current sensor, support camera sensor
		@param
		*   mainVehicleId: Vehicle index, configure order of web UI, starts from 0
		@param[in]
		*   cb: Groundtruth data fetch callback function
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetCameraSensorLaneInfoCB(void(*cb)(int mainVehicleId, int sensorId, SimOne_Data_LaneInfo *pLaneInfo));

		/*
		获得某个传感器信息(OSI格式)
		\li function:
		*	SensorData
		\li brief:
		*	Get OSISensorData imformations
		@param
		*   mainVehicleId: Vehicle index, configure order of web UI, starts from 0
		@param[out]
		*   ultrasonics: SensorData in OSI protobuf format(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool OSIGetSensorData(int mainVehicleId, int sensorId, SimOne_Data_OSI *pSensorData);

		/*!
		传感器信息更新回调
		\li function:
		*	OSISetSensorDataUpdateCB
		\li brief:
		*	Get SetSensorData for current vehicle in OSI format. Need a perfect perception sensor currently.
		@param
		*   mainVehicleId: Vehicle index, configure order of web UI, starts from 0
		@param[in]
		*   sensordata: SetSensorData fetch callback function
		@param[out]
		*   pSensorData: SensorData in OSI protobuf format(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool OSISetSensorDataUpdateCB(void(*cb)(int mainVehicleId, int sensorId, SimOne_Data_OSI *pSensorData));

		/*!
		获取理想传感器热区真值信息(OSI 格式)
		\li function:
		*	OSIGetGroundTruth
		\li brief:
		*	Get Ground Truth objects for current vehicle in OSI format. Need a ideal perception sensor currently.
		@param
		*   mainVehicleId: Vehicle index, configure order of web UI, starts from 0
		@param[out]
		*   pGroundtruth: Groundtruth data in OSI protobuf format(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool OSIGetGroundTruth(int mainVehicleId, SimOne_Data_OSI *pGroundtruth);

		/*!
		传感器真值信息更新回调
		\li function:
		*	OSISetGroundTruthUpdateCB
		\li brief:
		*	Get Ground Truth objects for current vehicle in OSI format. Need a perfect perception sensor currently.
		@param
		*   mainVehicleId: Vehicle index, configure order of web UI, starts from 0
		@param[in]
		*   groundtruth: groundtruth data fetch callback function
		@param[out]
		*   pGroundtruth: Groundtruth data in OSI protobuf format(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool OSISetGroundTruthUpdateCB(void(*cb)(int mainVehicleId, SimOne_Data_OSI *pGroundtruth));

		/*!
		获取SimOneDriver运行状态
		\li function:
		*	GetDriverStatus
		\li brief:
		*	Get SimOneDriver status
		@param
		*   mainVehicleId: Vehicle index, configure order of web UI, starts from 0
		@param[out]
		*   pDriverStatus: SimOneDriver status data(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetDriverStatus(const int mainVehicleId, SimOne_Data_Driver_Status* pDriverStatus);
#ifndef WITHOUT_HDMAP
		/*
		获得对应车辆编号V2X中的Basic Safety Message
		\li function:
		*	GetV2XBSMinfo
		\li brief:
		*	Get V2X Basic V2X imformation
		@param
		*   mainVehicleId: Vehicle index, configure order of web UI, starts from 0
		@param[out]
		*   V2XBSMinfo: V2XBSMinfo data in SimOne_Data_V2XBSM format(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetV2XBSMInfo(int mainVehicleId, int sensorId, SimOne_Data_V2XBSM *pDetections);

		/*
		获得对应车辆编号V2X中的Road Side Information
		\li function:
		*	GetV2XRSIinfo
		\li brief:
		*	Get V2X Road Side Information
		@param
		*   mainVehicleId: Vehicle index, configure order of web UI, starts from 0
		@param[out]
		*   V2XRSIinfo: V2XRSIinfo data in SimOne_Data_V2XRSI format(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetV2XRSIInfo(int mainVehicleId, int sensorId, SimOne_Data_V2XRSI *pDetections);

		/*
		获得对应车辆编号V2X中的SPAT Message
		\li function:
		*	GetV2XSPATinfo
		\li brief:
		*	Get V2X Spat Message
		@param
		*   mainVehicleId: Vehicle index, configure order of web UI, starts from 0
		@param[out]
		*   pDetections: V2XSPATinfo data in SimOne_Data_V2XSPAT format(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetV2XSPATInfo(int mainVehicleId, int sensorId, SimOne_Data_V2XSPAT *pDetections);
#endif

		/*!
		得到所有传感器的配置信息（Id、类型、频率、位置和朝向等）
		\li function:
		*	GetSensorConfigurations
		\li brief:
		*	Get Sensor's position information
		@param
		*    pSensorConfigurations: SensorConfigurations data (output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetSensorConfigurations(SimOne_Data_SensorConfigurations *pSensorConfigurations);

		/*!
		获取当前环境相关信息（天气、光照、地面等）
		\li function:
		*	GetEnvironment
		\li brief:
		*	Get current Environment
		@param
		*    pWeather: SimOne_Data_Environment data (output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetEnvironment(SimOne_Data_Environment *pEnvironment);

		/*!
		设置当前环境相关信息（天气、光照、地面等）
		\li function:
		*	SetEnvironment
		\li brief:
		*	Set Current Environment
		@param
		*    pWeather: SimOne_Data_Environment data (output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetEnvironment(SimOne_Data_Environment *pEnvironment);

		/*!
		设置车辆信号灯状态
		\li function:
		*	SetSignalLights
		\li brief:
		*	Set signal lights
		@param
		*   mainVehicleId: Vehicle index, configuration order from scenario editing, starting from 0
		@param[in]
		*	pTurnSignal: SimOne_Data_Turn_Signal data (output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetSignalLights(const int mainVehicleId, SimOne_Data_Signal_Lights *pSignalLights);

		/*!
		获取SimOneDriver运行状态
		\li function:
		*	GetDriverStatus
		\li brief:
		*	Get SimOneDriver status
		@param
		*   mainVehicleId: Vehicle index, configuration order from scenario editing, starting from 0
		@param[out]
		*   pDriverStatus: SimOneDriver status data(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetDriverStatus(const int mainVehicleId, SimOne_Data_Driver_Status* pDriverStatus);

		/*!
		获取SimOneDriver控制信号
		\li function:
		*	GetDriverControl
		\li brief:
		*	Get SimOneDriver drive control
		@param
		*   mainVehicleId: Vehicle index, configure order of web UI, starts from 0
		@param[out]
		*   pControl: vehicle control data from SimOneDriver(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetDriverControl(const int mainVehicleId, SimOne_Data_Control* pControl);

		/*!
		获取案例主车路径点
		\li function:
		*	GetWayPoints
		\li brief:
		*	Get MainVehile WayPoints
		@param
		*   mainVehicleId: Vehicle index, configure order of web UI, starts from 0
		@param[out]
		*   pWayPoints: MainVehicle WayPoints data(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetWayPoints(SimOne_Data_WayPoints* pWayPoints);

		/*!
		场景事件回调
		\li function:
		*	SetScenarioEventCB
		\li brief:
		*	Add scenario event callback
		@param[in]
		*   cb: scenario event callback function
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetScenarioEventCB(void(*cb)(int mainVehicleId, const char* event, const char* data));

		/*!
		获取高精度地图标识
		\li function:
		*	GetHDMapData
		\li brief:
		*	Get hdmap data which is configured by SimOne web app.
		@param
		*   hdMap: SimOne_Data_Map.
		@return
		*	True when get HDMap data success, else returns false.
		*/
		SIMONE_NET_API bool GetHDMapData(SimOne_Data_Map& hdMap);

#ifndef WITHOUT_HDMAP

		/*!
		加载高精度地图
		\li function:
		*	LoadHDMap
		\li brief:
		*	Load hdmap which is configured by SimOne web app.
		@param
		*   timeOutSeconds: Timeout setting to repeatedly check whether hdmap is ready to load. Will stop and return when time is up.
		@return
		*	True when hdmap is loaded with success, else returns false.
		*/
		SIMONE_NET_API bool LoadHDMap(const int& timeOutSeconds);

		/*!
		获取最接近输入点的车道，所属车道优先
		\li function:
		*	GetNearMostLane
		\li brief:
		*	Get the lane which is near most to or geometry overlapping the input point. When there are more than one lane's geometry overlaps the input point, will pick the distance near most one.
		@param
		*   pos: Input 3d location.
		@param[out]
		*   id: Lane ID of founded lane. ID with this format roadId_sectionIndex_laneId.
		@param[out]
		*   s, t: The input point's value pair in s-t coordinate system, relative to the found lane.
		@param[out]
		*   s_toCenterLine, t_toCenterLine: is the input point's value pair in s-t coordinate system, relative to the found lane's owner road's center line.
		*   Values are fuzzy accurate, please use API GetRoadST for highly accurate values for [s_toCenterLine, t_toCenterLine].
		@return
		*	True when any lane is found, else returns false.
		*/
		SIMONE_NET_API bool GetNearMostLane(const SSD::SimPoint3D& pos, SSD::SimString& id, double& s, double& t, double& s_toCenterLine, double& t_toCenterLine);

		/*!
		获取临近车道列表
		\li function:
		*	GetNearLanes
		\li brief:
		*	Get near lanes which are close to the input point in a specified range.
		@param
		*   pos: Input 3d location.
		@param
		*   distance: Input range distance.
		@param[out]
		*   nearLanes: Lane IDs of founded lanes. Each ID with this format roadId_sectionIndex_laneId.
		@return
		*	True when any lane(lanes) is(are) found, else returns false.
		*/
		SIMONE_NET_API bool GetNearLanes(const SSD::SimPoint3D& pos, const double& distance, SSD::SimStringVector& nearLanes);

		/*!
		获取视野范围内所有车道
		\li function:
		*	GetNearLanesWithAngle
		\li brief:
		*	Get near lanes which are close to the input point in a specified range and also heading to within a specified angle range in 2d-inertial system.
		@param
		*   pos: Input 3d location.
		@param
		*   distance: Input distance range to search.
		@param
		*   headingAngle: A specified heading direction's angle relative to x-axis in 2d-inertial system. headingAngle is defined as radian.
		@param
		*   angleShift: To help define the range of angle as [headingAngle - angleShift, headingAngle + angleShift], and angleShift is defined as radian.
		@param[out]
		*   nearLanes: Lane IDs of founded lanes. Each ID with this format roadId_sectionIndex_laneId.
		@return
		*	True when any lane(lanes) is(are) found, else returns false.
		*/
		SIMONE_NET_API bool GetNearLanesWithAngle(const SSD::SimPoint3D& pos, const double& distance,
			const double& headingAngle, const double& angleShift, SSD::SimStringVector& nearLanes);

		/*!
		获取离最近车道左右边缘线的距离
		\li function:
		*	GetDistanceToLaneBoundary
		\li brief:
		*	Get the distance info to the near most lane's left and right boundaries
		@param
		*   pos: Input 3d location.
		@param[out]
		*   id: Lane ID of founded lane. ID with this format roadId_sectionIndex_laneId.
		@param[out]
		*   distToLeft, distToRight: The distance to boundaries in 3d space.
		*   distToLeft2D, distToRight2D: The distance to boundaries in 2d space(ignore height)
		@return
		*	True if near most lane is found, else returns false.
		*/
		SIMONE_NET_API bool GetDistanceToLaneBoundary(const SSD::SimPoint3D& pos, SSD::SimString& id, double& distToLeft, double& distToRight, double& distToLeft2D, double& distToRight2D);

		/*!
		获取车道信息(包含车道ID，左右边缘线，虚拟中心线)
		\li function:
		*	GetLaneSample
		\li brief:
		*	 Get lane sample info.
		@param
		*   id: Input lane ID. ID with this format roadId_sectionIndex_laneId.
		@param[out]
		*   info: Lane information(HDMapStandalone::MLaneInfo) of specified lane.
		@return
		*	True if specified lane exists in the map, else returns false.
		*/
		SIMONE_NET_API bool GetLaneSample(const SSD::SimString &id, HDMapStandalone::MLaneInfo& info);

		/*!
		获取车道连接信息
		\li function:
		*	GetLaneLink
		\li brief:
		*	 Get lane's link information based on lane's ID
		@param
		*   id: Input lane ID. ID with this format roadId_sectionIndex_laneId.
		@param[out]
		*   laneLink: Lane link information(HDMapStandalone::MLaneLink) of specified lane.
		@return
		*	True if specified lane exists in the map, else returns false.
		*/
		SIMONE_NET_API bool GetLaneLink(const SSD::SimString& id, HDMapStandalone::MLaneLink& laneLink);

		/*!
		获取车道类型
		\li function:
		*	GetLaneType
		\li brief:
		*	 Get lane's type
		@param
		*   id: Input lane ID. ID with this format roadId_sectionIndex_laneId.
		@param[out]
		*   laneType: Lane type of specified lane.
		@return
		*	True if specified lane exists in the map, else returns false.
		*/
		SIMONE_NET_API bool GetLaneType(const SSD::SimString& id, HDMapStandalone::MLaneType& laneType);

		/*!
		获取车道宽度
		\li function:
		*	GetLaneWidth
		\li brief:
		*	 Get lane's width in bitangent direction of specified point.
		@param
		*   id: Input lane ID. ID with this format roadId_sectionIndex_laneId.
		@param
		*   pos: Input 3d location.
		@param[out]
		*   width: lane width of specified lane.
		@return
		*	True if specified lane exists in the map, else returns false.
		*/
		SIMONE_NET_API bool GetLaneWidth(const SSD::SimString& id, const SSD::SimPoint3D& pos, double& width);

		/*!
		获取相对于车道虚拟中心线的ST坐标
		\li function:
		*	GetLaneST
		\li brief:
		*	 Get the [s, t] value pair in s-t coordinate system relative to the lane's center line
		@param
		*   id: Input lane ID. ID with this format roadId_sectionIndex_laneId.
		@param
		*   pos: Input 3d location.
		@param[out]
		*   s, t: The input point's value pair in s-t coordinate system, relative to specified lane.
		@return
		*	True if specified lane exists in the map, else returns false.
		*/
		SIMONE_NET_API bool GetLaneST(const SSD::SimString& id, const SSD::SimPoint3D& pos, double& s, double& t);

		/*!
		获取相对于道路参考线的ST坐标
		\li function:
		*	GetRoadST
		\li brief:
		*	 Get the [s, t] value pair in s-t coordinate system relative to the lane's owner road's reference line
		@param
		*   id: Input lane ID. ID with this format roadId_sectionIndex_laneId.
		@param
		*   pos: Input 3d location.
		@param[out]
		*   s, t, z: [s, t] represents the input point's value pair in s-t coordinate system, and z represents the input point's height value in localENU.
		@return
		*	True if specified lane exists in the map, else returns false.
		*/
		SIMONE_NET_API bool GetRoadST(const SSD::SimString& id, const SSD::SimPoint3D& pos, double& s, double& t, double& z);

		/*!
		根据车道ST坐标获取局部坐标
		\li function:
		*	GetInertialFromLaneST
		\li brief:
		*	 Get [x, y, z] position in localENU, based on [s, t] value pair in s-t coordinate system relative to the lane's center line
		@param
		*   id: Input lane ID. ID with this format roadId_sectionIndex_laneId.
		@param
		*   s, t: [s, t] represents the input point's value pair in s-t coordinate system
		@param[out]
		*   inertial: The [x, y, z] position in localENU.
		*   dir: The direction in localENU on lane middle line.
		@return
		*	True if specified lane exists in the map, else returns false.
		*/
		SIMONE_NET_API bool GetInertialFromLaneST(const SSD::SimString& id, const double& s, const double& t, SSD::SimPoint3D& inertial, SSD::SimPoint3D& dir);

		/*!
		查询指定车道是否存在于地图之中
		\li function:
		*	ContainsLane
		\li brief:
		*	Check whether lane exists in current map.
		@param
		*   id: Input lane ID. ID with this format roadId_sectionIndex_laneId.
		@return
		*	True if exists, else returns false.
		*/
		SIMONE_NET_API bool ContainsLane(const SSD::SimString& id);

		/*!
		获取地图中停车位列表
		\li function:
		*	GetParkingSpaceList
		\li brief:
		*	Get parkingSpace list in the map
		@param[out]
		*   ids: Parking space list.
		*/
		SIMONE_NET_API void GetParkingSpaceList(SSD::SimVector<HDMapStandalone::MParkingSpace>& parkingSpaceList);

		/*!
		获取预设规划路径
		\li function:
		*	GetPredefinedRoute
		\li brief:
		*	Get predefined route
		@param[out]
		*   route: Generated route.
		@return
		*	True if any route has been generated, else returns false.
		*/
		SIMONE_NET_API bool GetPredefinedRoute(SSD::SimPoint3DVector& route);

		/*!
		获取路网路径规划
		\li function:
		*	GenerateRoute
		\li brief:
		*	Generate route for specified input points
		@param
		*   inputPoints: Input points that to guide generated route should pass over
		@param[out]
		*   indexOfValidPoints: Pick valid ones from input points. Valid ones will be used for generting route.
		@param[out]
		*   route: Generated route.
		@return
		*	True if any route has been generated, else returns false.
		*/
		SIMONE_NET_API bool GenerateRoute(const SSD::SimPoint3DVector& inputPoints, SSD::SimVector<int>& indexOfValidPoints, SSD::SimPoint3DVector& route);

		/*!
		获取规划路径所途径道路的ID列表
		\li function:
		*	Navigate
		\li brief:
		*	Provide routing path throughed road id list.
		@param
		*   inputPoints: Input points that to guide generated route should pass over
		@param[out]
		*   indexOfValidPoints: Pick valid ones from input points. Valid ones will be used for generating route.
		@param[out]
		*   roadIdList: road id list that are throughed by routing path.
		@return
		*	True if any route has been generated, else returns false.
		*/
		SIMONE_NET_API bool Navigate(const SSD::SimPoint3DVector& inputPoints, SSD::SimVector<int>& indexOfValidPoints, SSD::SimVector<long>& roadIdList);

		/*!
		根据指定车道id和局部坐标获取输入点左右两侧车道标线信息
		\li function:
		*	GetRoadMark
		\li brief:
		*	Get left and right roadmarks for specified input point and specified lane
		@param
		*   pos: Input 3d location.
		@param
		*   id: Input lane ID. ID with this format roadId_sectionIndex_laneId.
		@param[out]
		*   left: Left side roadmark.
		@param[out]
		*   right: Right side roadmark.
		@return
		*	True if roadmark is found, else returns false.
		*/
		SIMONE_NET_API bool GetRoadMark(const SSD::SimPoint3D& pos, const SSD::SimString& id, HDMapStandalone::MRoadMark& left, HDMapStandalone::MRoadMark& right);

		/*!
		获取地图中信号灯列表
		\li function:
		*	GetTrafficLightList
		\li brief:
		*	Get traffic light list in the map.
		@param[out]
		*   list: Traffic light object list.
		*/
		SIMONE_NET_API void GetTrafficLightList(SSD::SimVector<HDMapStandalone::MSignal>& list);

		/*!
		获取地图中交通标志列表
		\li function:
		*	GetTrafficSignList
		\li brief:
		*	Get traffic sign list in the map.
		@param[out]
		*   list: Traffic sign object list.
		*/
		SIMONE_NET_API void GetTrafficSignList(SSD::SimVector<HDMapStandalone::MSignal>& list);

		/*!
		获取交通灯给定作用车道的关联停止线列表
		\li function:
		*	GetStoplineList
		\li brief:
		*	Get the list of stoplines that belongs to traffic light's validity matched to specified lane.
		@param
		*   light: Traffic light object.
		@param
		*   id: Input lane ID. ID with this format roadId_sectionIndex_laneId.
		@param[out]
		*   stoplineList: Stoplines list that is associated.
		*/
		SIMONE_NET_API void GetStoplineList(const HDMapStandalone::MSignal& light, const SSD::SimString& id, SSD::SimVector<HDMapStandalone::MObject>& stoplineList);

		/*!
		获取交通灯给定作用车道的关联人行横道线列表
		\li function:
		*	GetCrosswalkList
		\li brief:
		*	Get the list of crosswalks that belongs to traffic light's validity matched to specified lane.
		@param
		*   light: Traffic light object.
		@param
		*   id: Input lane ID. ID with this format roadId_sectionIndex_laneId.
		@param[out]
		*   stoplineList: Crosswalks list that is associated.
		*/
		SIMONE_NET_API void GetCrosswalkList(const HDMapStandalone::MSignal& light, const SSD::SimString& id, SSD::SimVector<HDMapStandalone::MObject>& crosswalkList);

		/*!
		获取指定车道所在道路上的网状线列表
		\li function:
		*	GetCrossHatchList
		\li brief:
		*	Get the list of cross hatch in the specified lane's road neighborhood.
		@param
		*   id: Input lane ID. ID with this format roadId_sectionIndex_laneId.
		@param[out]
		*   stoplineList: Cross hatches list that is associated.
		*/
		SIMONE_NET_API void GetCrossHatchList(const SSD::SimString& id, SSD::SimVector<HDMapStandalone::MObject>& crossHatchList);

		/*!
		获取输入点投影到指定车道中心线上的点和切线方向
		\li function:
		*	GetLaneMiddlePoint
		\li brief:
		*	Get target point that the input point is reflected onto specified lane's middle line.
		@param
		*   inputPt: Input 3d location.
		@param[out]
		*   id: Lane ID of founded lane. ID with this format roadId_sectionIndex_laneId.
		@param[out]
		*   targetPoint: The target point that is on specified lane's middle line.
		@param[out]
		*   dir: The tangent direction on the target point on lane's middle line.
		@return
		*	True when any lane is found, else returns false.
		*/
		SIMONE_NET_API bool GetLaneMiddlePoint(const SSD::SimPoint3D& inputPt, const SSD::SimString& id, SSD::SimPoint3D& targetPoint, SSD::SimPoint3D& dir);

		/*!
		获取路网指定坐标点的高程列表
		\li function:
		*	GetHeights
		\li brief:
		*	Get height list of input point's radius area that covers in the map.
			The point may in vertical intersect with multiple roads with different heights, e.g. at highway or tunnel.
		@param
		*   inputPt: Input 3d location.
		@param[out]
		*   radius: Radius indicates how far away to detect in circle. It should be set larger than 3 meters in length. Setting as 3 meters is recommended.
		@param[out]
		*   heights: Returns heights/one height.
		@param[out]
		*   roadIds: Returns the road ids that the target height is based one.
		@param[out]
		*   insideRoadStates: Returns whether inputPt is inside the target roads or not.
		@return
		*	True if any height is found, else returns false.
		*/
		SIMONE_NET_API bool GetHeights(const SSD::SimPoint3D& inputPt, const double& radius, SSD::SimVector<double>& heights,
			SSD::SimVector<long>& roadIds, SSD::SimVector<bool>& insideRoadStates);
#endif
		/*!
		场景事件回调
		\li function:
		*	SetScenarioEventCB
		\li brief:
		*	Add scenario event callback
		@param[in]
		*   cb: scenario event callback function
		@param
		*	mainVehicleId: Vehilcle index, configure order of web UI, starts from 0
		*	event: Command sent to the mainVehicle
		*	data: Not used yet
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetScenarioEventCB(void(*cb)(int mainVehicleId, const char* event, const char* data));

	}
#ifdef __cplusplus
}
#endif
