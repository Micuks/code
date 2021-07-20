////
// Created By: Huiyong.Men 2019/07/09
//
//-----------------------------------------------------
// ***Warning*** This file MUST match SimOneIOStruct.py
//-----------------------------------------------------
// 
#pragma once
#include <vector>
#include <map>
#ifndef WITHOUT_HDMAP
	#include "SSD/SimVector.h"
	#include "Message.hpp"
#endif
#include <time.h>
#pragma pack(push) 
#pragma pack(1)
struct SimOne_Data
{
	long long timestamp = 0; // timestamp millisecond
	int frame;
	int version = 0; // API version
};
struct SimOneData_Vec3f
{
	float x;
	float y;
	float z;
};
// ----------------------------
// SimOne Map (SimOne Output) 
// ----------------------------
#define SOSM_CASE_START_EVENT_LABEL "SOSM_CASE_EVENT_START"
#define SOSM_CASE_STOP_EVENT_LABEL "SOSM_CASE_EVENT_STOP"

#define SOSM_MAP_LABEL "SOSM_MAP"
#define SOSM_MAP_OD_LENGT 128
#define SOSM_MAP_ODURL_LENGT 256
#define SOSM_MAP_ODMD5_LENGT 128

#define SOSM_CASENAME_LENGTH 256
#define SOSM_CASEID_LENGT 256
#define SOSM_TASKID_LENGT 256
#define SOSM_SESSIONID_LENGT 256
struct SimOne_Data_Map
{
	char openDrive[SOSM_MAP_OD_LENGT];
	char openDriveUrl[SOSM_MAP_ODURL_LENGT];
	char opendriveMd5[SOSM_MAP_ODMD5_LENGT];
};
// ----------------------------
// SimOne MainVehilce WayPoints (SimOne Output) 
// ----------------------------
#define SOSM_WAYPOINTS_LABEL "SOSM_WAYPOINTS"
#define SOSM_WAYPOINTS_SIZE_MAX 100
struct SimOne_Data_WayPoints_Entry 
{
	int index;
	float posX; // MainVehicle WayPoints X on Opendrive (by meter)
	float posY; // MainVehicle WayPoints Y on Opendrive (by meter)

	float heading_x;
	float heading_y;
	float heading_z;
	float heading_w;
};

struct SimOne_Data_WayPoints:public SimOne_Data
{
	int wayPointsSize; // MainVehicle WayPoints size
	SimOne_Data_WayPoints_Entry wayPoints[SOSM_WAYPOINTS_SIZE_MAX]; // WayPoints, 100 max
};
// ----------------------------
// Vehicle pose control data (SimOne Input) 
// ----------------------------
#define SOSM_POSE_CONTROL_PREFIX "SOSM_POSE_CONTROL_"
struct SimOne_Data_Pose_Control : public SimOne_Data
{
	float posX; // Position X on Opendrive (by meter)
	float posY; // Position Y on Opendrive (by meter)
	float posZ; // Position Z on Opendrive (by meter)
	float oriX; // Rotation X on Opendrive (by radian)
	float oriY; // Rotation Y on Opendrive (by radian)
	float oriZ; // Rotation Z on Opendrive (by radian)
	bool autoZ = false;// Automatically set Z according to scene
};

#define OSI_API_STRAT_CONTROL "SOSM_OSI_API_STRAT_CONTROL"
struct OSI_API_Control
{
	bool OSIAPI_Control = false;
};
// ----------------------------
// Vehicle control data (SimOne Input)
// ----------------------------
#define SOSM_CONTROL_PREFIX "SOSM_CONTROL_"

// Vehicle control data (SimOne Input)
// ----------------------------
#define SOSM_DRIVER_CONTROL_PREFIX "SOSM_DRIVER_CONTROL_"

enum EGearMode
{
	EGearMode_Neutral = 0,
	EGearMode_Drive = 1,      // forward gear for automatic gear
	EGearMode_Reverse = 2,
	EGearMode_Parking = 3,

	EGearManualMode_1 = 4,    // forward gear 1 for manual gear
	EGearManualMode_2 = 5,
	EGearManualMode_3 = 6,
	EGearManualMode_4 = 7,
	EGearManualMode_5 = 8,
	EGearManualMode_6 = 9,
	EGearManualMode_7 = 10,
	EGearManualMode_8 = 11
};

enum EThrottleMode
{                                     
    EThrottleMode_Percent = 0,         //[0, 1]                                                            
    EThrottleMode_Torque = 1,          //engine torque, N.m                                                
    EThrottleMode_Speed = 2,           //vehicle speed, m/s,   in this mode, brake input is ignored        
    EThrottleMode_Accel = 3,           //vehicle acceleration, m/s^2, in this mode, brake input is ignored 
    EThrottleMode_EngineAV = 4,        //engine, rpm                                                       
    EThrottleMode_WheelTorque = 5,     //torques applied to each wheel, array, size is the wheel number, N.m
};

enum EBrakeMode
{
    EBrakeMode_Percent = 0,                 // [0, 1], factor of max brake pressure
    EBrakeMode_MasterCylinderPressure = 1,  // MPa
    EBrakeMode_PedalForce = 2,              // N
    EBrakeMode_WheelCylinderPressure = 3,   // Mpa for each wheel
    EBrakeMode_WheelTorque = 4              // Nm for each wheel
};
enum ESteeringMode
{
    ESteeringMode_Percent = 0,            // [-1, 1], left turn is negative, right is positive
    ESteeringMode_SteeringWheelAngle = 1, // steering wheel angle, degree
    ESteeringMode_Torque = 2,             // torque to steering wheel, N.m
    ESteeringMode_AngularSpeed = 3,       // steering wheel angualr speed, degree/s
    ESteeringMode_WheelAngle = 4,         // degree for each wheel
    ESteeringMode_WheelAnglarSpeed = 5,   // degree/s for each wheel
};
enum ELogLevel_Type
{
	ELogLevelDebug = 0,
	ELogLevelInformation = 1,
	ELogLevelWarning = 2,
	ELogLevelError = 3,
	ELogLevelFatal = 4
};

// For each control modes, the support status is listed below:
//      Mode                         SimOneDynamics     CarSim/TruckSim
// EThrottleMode_Percent                   Yes                Yes
// EThrottleMode_Torque                    Yes                Yes
// EThrottleMode_Speed                     Yes                Yes
// EThrottleMode_Accel                     Yes                Yes
// EThrottleMode_EngineAV                  No                 Yes
// EThrottleMode_WheelTorque               No                 Yes
// EBrakeMode_Percent                      Yes                Yes
// EBrakeMode_MasterCylinderPressure       Yes                Yes
// EBrakeMode_PedalForce                   Yes                Yes
// EBrakeMode_WheelCylinderPressure        No                 Yes
// EBrakeMode_WheelTorque                  No                 Yes
// ESteeringMode_Percent                   Yes                Yes
// ESteeringMode_SteeringWheelAngle        Yes                Yes
// ESteeringMode_Torque                    Yes                Yes
// ESteeringMode_AngularSpeed              Yes                Yes
// ESteeringMode_WheelAngle                No                 Yes
// ESteeringMode_WheelAnglarSpeed          No                 Yes

#define SO_MAX_WHEEL_NUM  20
struct SimOne_Data_Control : public SimOne_Data
{
    EThrottleMode throttleMode = EThrottleMode_Percent;
	float throttle;
    EBrakeMode brakeMode = EBrakeMode_Percent;
	float brake;
    ESteeringMode steeringMode = ESteeringMode_Percent;
	float steering;
	bool handbrake = false;
	bool isManualGear = false;
	// gear location
	EGearMode  gear;

    float clutch;

    // array data for throttle input when throttle mode is EThrottleMode_WheelTorque
    // the data sequence is: L1 (left wheel of alxe 1), R1 (right wheel of alxe 1),
    //                       L2, R2, L3, R3...
    float throttle_input_data[SO_MAX_WHEEL_NUM];
    // array data for brake input when throttle mode is EBrakeMode_WheelCylinderPressure or
    // EBrakeMode_WheelTorque
    float brake_input_data[SO_MAX_WHEEL_NUM];
    // array data for steering input when throttle mode is ESteeringMode_WheelAngle,
    // ESteeringMode_WheelAnglarSpeed
    float steering_input_data[SO_MAX_WHEEL_NUM];
};

struct SimOne_Trajectory_Point
{
    float posx;          // position x
    float posy;          // position y
    float speed;         // m/s
    float accel;         // accelelation m/s^2
    float theta;         // yaw   rad
    float kappa;         // curvature
    float relative_time; // time relative to the first trajectory point
    float s;             // distance from the first trajectory point
};

#define SO_MAX_TRAJECTORY_POINT_NUM 500
struct SimOne_Data_Control_Trajectory : public SimOne_Data
{
    int point_num;
    SimOne_Trajectory_Point points[SO_MAX_TRAJECTORY_POINT_NUM];
    bool isReverse;
};

struct SimOne_Data_ESP_Control : public SimOne_Data
{
	int stopDistance;
	float velocityLimit;
	float steering;
	float steerTorque;
	float accel;
	float accelUpperLimit;
	float accelLowerLimit;
	float accelUpperComfLimit;
	float accelLowerComfLimit;
	bool standStill;
	bool driveOff;
	int brakeMode;
	int vlcShutdown;
	int gearMode;
};

// ----------------------------
// Vehicle Event Information data (SimOne Input)
// ----------------------------
#define SOSM_VEHICLE_EVENT_PREFIX "SOSM_VEHICLE_EVENT_"

enum ESimone_Vehicle_EventInfo_Type
{
	//ESimOne_VehicleEventInfo_Forward_Collision = 0,
	//ESimOne_VehicleEventInfo_Backward_Collision = 1,
	//ESimOne_VehicleEventInfo_Left_Turn = 2,
	//ESimOne_VehicleEventInfo_Right_Turn = 3,
	//ESimOne_VehicleEventInfo_Forward_Straight =4,
	//ESimOne_VehicleEventInfo_Over_Speed = 5
	ESimOne_VehicleEventInfo_Forward_Collision_Warning = 0,		// 	front_crash_warning
	ESimOne_VehicleEventInfo_Backward_Collision_Warning = 1,	// 	back_crash_warning
	ESimOne_VehicleEventInfo_Left_Turn_Decision = 2,			// 	turn_left
	ESimOne_VehicleEventInfo_Left_Turn_Warning = 3,				// 	left_warning
	ESimOne_VehicleEventInfo_Right_Turn_Decision = 4,			// 	turn_right
	ESimOne_VehicleEventInfo_Right_Turn_Warning = 5,			// 	right_warning
	ESimOne_VehicleEventInfo_Forward_Straight_Decision = 6,		// 	straight_through
	ESimOne_VehicleEventInfo_Forward_Straight_Warning = 7,		// 	straight_warning
	ESimOne_VehicleEventInfo_Over_Speed_Warning = 8,			// 	overspeeding_warning
	ESimOne_VehicleEventInfo_Lane_Change_Decision = 9,			//  lane_change
	ESimOne_VehicleEventInfo_Lane_Change_Warning = 10,			// 	lane_change_warning
	ESimOne_VehicleEventInfo_Overtake_Decision = 11,			// 	overtake
	ESimOne_VehicleEventInfo_Emergency_Braking_Decision = 12,	// 	emergency_braking
	ESimOne_VehicleEventInfo_Accelerate_Decision = 13			// 	accelerate

};

struct SimOne_Data_Vehicle_EventInfo : public SimOne_Data
{
	ESimone_Vehicle_EventInfo_Type  type;
};

// ----------------------------
// Trajectory planning data (SimOne Input, for display) 
// ----------------------------
#define SOSM_TRAJECTORY_PREFIX "SOSM_TRAJECTORY_"
#define SOSM_TRAJECTORY_SIZE_MAX 100

struct SimOne_Data_Trajectory_Entry
{
	float posX; // Trajectory Position X on Opendrive (by meter)
	float posY; // Trajectory Position Y on Opendrive (by meter)
	float vel;  // Velocity (by meter/second)
};

struct SimOne_Data_Trajectory : public SimOne_Data
{
	int trajectorySize; // Trajectory size
	SimOne_Data_Trajectory_Entry trajectory[SOSM_TRAJECTORY_SIZE_MAX]; // Trajectory, 100 max
};

// ----------------------------
//  MianVehicle data (SimOne Output) 
// ----------------------------
#define SOSM_POSE_PREFIX "SOSM_POSE_"
#define SOSM_EXTRA_STATES_SIZE_MAX 256
struct SimOne_Data_Gps : public SimOne_Data
{
	float posX; // Position X on Opendrive (by meter)
	float posY; // Position Y on Opendrive (by meter)
	float posZ; // Position Z on Opendrive (by meter)
	float oriX; // Rotation X on Opendrive (by radian)
	float oriY; // Rotation Y on Opendrive (by radian)
	float oriZ; // Rotation Z on Opendrive (by radian)
	float velX; // MainVehicle Velocity X on Opendrive (by meter)
	float velY; // MainVehicle Velocity Y on Opendrive (by meter)
	float velZ; // MainVehicle Velocity Z on Opendrive (by meter)
	float throttle; //MainVehicle throttle
	float brake; //MainVehilce brake;
	float steering; //MainVehicle Wheel Steering angle (deg)
	int gear; // MainVehicle gear position
	float accelX; // MainVehilce Acceleration X on Opendrive (by meter)
	float accelY; // MainVehilce Acceleration Y on Opendrive (by meter)
	float accelZ; // MainVehilce Acceleration Z on Opendrive (by meter)
	float angVelX; // MainVehilce Angular Velocity X on Opendrive (by meter)
	float angVelY; // MainVehilce Angular Velocity Y on Opendrive (by meter)
	float angVelZ; // MainVehilce Angular Velocity Z on Opendrive (by meter)
	float wheelSpeedFL;  // Speed of front left wheel (by meter/sec)
	float wheelSpeedFR;  // Speed of front right wheel (by meter/sec)
	float wheelSpeedRL;  // Speed of rear left wheel (by meter/sec)
	float wheelSpeedRR;  // Speed of rear right wheel (by meter/sec)
	float engineRpm;// Speed of engine (by r/min)
	float odometer;	// odometer in meter.
	int extraStateSize;
	float extraStates[SOSM_EXTRA_STATES_SIZE_MAX];// vehicle states subscripted by MainVehicleExtraDataIndics message
};

enum SimOne_Data_Vehicle_State
{
    SO_M_SW,       // Steering wheel torque, unit: N.m
	S0_Vx_SM,      // Sprung Mass CG Vx
	S0_Vy_SM,      // Sprung Mass CG Vy
	S0_Vz_SM,      // Sprung Mass CG Vz
	SO_M_ENGOUT,   // Engine Output Torque
	SO_My_DR_L1,      // Wheels Driving Torque
	SO_My_DR_R1,
	SO_My_DR_L2,
	SO_My_DR_R2,
	SO_My_DR_L3,
	SO_My_DR_R3,

	SO_F_Pedal,    // Brake Pedal Force
	SO_Pbk_Con,    // BrakeMasterCylinder Pressure
	SO_My_Bk_L3,   // Brake Torque at Left Rear Wheel
	SO_My_Bk_R3,   // Brake Torque at Right Rear Wheel

	SO_ClutchTr,   // Transmission clutch control

    SO_X_L1,       // x coordinate, wheel center L1
    SO_Y_L1,
    SO_Z_L1,
    SO_X_L2,
    SO_Y_L2,
    SO_Z_L2,
    SO_X_R1,
    SO_Y_R1,
    SO_Z_R1,
    SO_X_R2,
    SO_Y_R2,
    SO_Z_R2,
	SO_X_L3,       // x coordinate, wheel center L3
	SO_Y_L3,
	SO_Z_L3,
	SO_X_R3,
	SO_Y_R3,
	SO_Z_R3,

    SO_Xctc_L1,      // x coordinate, center of tire contact L1
    SO_Yctc_L1,      // y coordinate, center of tire contact L1
    SO_Zctc_L1,      // z coordinate, center of tire contact L1
    SO_Xctc_L2,
    SO_Yctc_L2,
    SO_Zctc_L2,
    SO_Xctc_R1,
    SO_Yctc_R1,
    SO_Zctc_R1,
    SO_Xctc_R2,
    SO_Yctc_R2,
    SO_Zctc_R2,

    SO_AVy_L1,     // Wheel L1 spin    unit: rpm
    SO_Kappa_L1,   // Longitudinal slip, tire L1   ratio, no unit
    SO_Alpha_L1,   // Lateral slip angle, tire L1  unit: degree
    SO_Fz_L1,      // Vertical force, tire L1   unit: N
    SO_My_WC_L1,   // Tire My at wheel center L1   unit: N.m
    SO_Fx_L1,      // Longitudinal force, tire L1   unit: N
    SO_Fy_L1,      // lateral force, tire L1  unit: N
    SO_Jnc_L1,     // Wheel L1 jounce (compression)   unit: mm
    SO_JncR_L1,    // Wheel L1 jounce rate         unit: mm/s
    SO_Mz_L1,      // Aligning moment, tire L1   unit: Nm

    SO_AVy_L2,     //  Wheel L2 spin    unit: rpm
    SO_Kappa_L2,   // Longitudinal slip, tire L2   ratio, no unit
    SO_Alpha_L2,   // Lateral slip angle, tire L2  unit: rad
    SO_Fz_L2,
    SO_My_WC_L2,
    SO_Fx_L2,       // Longitudinal force, tire L2
    SO_Fy_L2,       // lateral force, tire L2
    SO_Jnc_L2,      // Wheel L2 jounce (compression)  unit: cm
    SO_JncR_L2,     // Wheel L2 jounce rate   unit: cm/s
    SO_Mz_L2,       // Aligning moment, tire L2  unit: Nm

    SO_AVy_R1,
    SO_Kappa_R1,
    SO_Alpha_R1,    // Lateral slip angle, tire R1  unit: degree
    SO_Fz_R1,
    SO_My_WC_R1,
    SO_Fx_R1,       // Longitudinal force, tire R1
    SO_Fy_R1,       // lateral force, tire R1
    SO_Jnc_R1,      // Wheel R1 jounce (compression)
    SO_JncR_R1,     // Wheel R1 jounce rate
    SO_Mz_R1,       // Aligning moment, tire R1

    SO_AVy_R2,
    SO_Kappa_R2,
    SO_Alpha_R2,    // Lateral slip angle, tire R2  unit: degree
    SO_Fz_R2,
    SO_My_WC_R2,
    SO_Fx_R2,       // Longitudinal force, tire R2
    SO_Fy_R2,       // lateral force, tire R2
    SO_Jnc_R2,      // Wheel R2 jounce (compression)
    SO_JncR_R2,     // Wheel R2 jounce rate
    SO_Mz_R2,       // Aligning moment, tire R2

	SO_AVy_L3,     // Wheel L3 spin    unit: rpm
	SO_Kappa_L3,   // Longitudinal slip, tire L3   ratio, no unit
	SO_Alpha_L3,   // Lateral slip angle, tire L3  unit: degree
	SO_Fz_L3,      // Vertical force, tire L3   unit: N
	SO_My_WC_L3,   // Tire My at wheel center L3   unit: N.m
	SO_Fx_L3,      // Longitudinal force, tire L3   unit: N
	SO_Fy_L3,      // lateral force, tire L3  unit: N
	SO_Jnc_L3,     // Wheel L3 jounce (compression)   unit: mm
	SO_JncR_L3,    // Wheel L3 jounce rate         unit: mm/s
	SO_Mz_L3,      // Aligning moment, tire L3   unit: Nm

	SO_AVy_R3,
	SO_Kappa_R3,
	SO_Alpha_R3,    // Lateral slip angle, tire R3  unit: degree
	SO_Fz_R3,
	SO_My_WC_R3,
	SO_Fx_R3,       // Longitudinal force, tire R3
	SO_Fy_R3,       // lateral force, tire R3
	SO_Jnc_R3,      // Wheel R3 jounce (compression)
	SO_JncR_R3,     // Wheel R3 jounce rate
	SO_Mz_R3,       // Aligning moment, tire R3

	SO_Steer_L3,
	SO_Steer_R3,

    SO_Steer_SW,   // Steering wheel angle  unit: deg
};

#define SOSM_VEHICLE_EXTRA_STATE_MAX_SIZE 600
struct SimOne_Data_Vehicle_Extra
{
    int dataSize;
    float extra_states[SOSM_VEHICLE_EXTRA_STATE_MAX_SIZE];
};

#define SOSM_MAIN_VEHICLE "SOSM_MAIN_VEHICLE"
struct SimOne_Data_MainVehicle : public SimOne_Data
{
	int mainVehicleId;				// MainVehicle ID
	float posX; 					// Position X on Opendrive (by meter)
	float posY; 					// Position Y on Opendrive (by meter)
	float posZ; 					// Position Z on Opendrive (by meter)
	float oriX; 					// Rotation X on Opendrive (by radian)
	float oriY; 					// Rotation Y on Opendrive (by radian)
	float oriZ; 					// Rotation Z on Opendrive (by radian)
	float speed;					// MainVehicle speed
	int nextTrafficLightColorId;	// current traffic lisght 0-read 1-yellow 2-green 3-unknown
	int gear; 						// MainVehicle gear position
	float throttle; 				// MainVehicle throttle
	float brake; 					// MainVehicle brake;
	float steering; 				// MainVehicle Steering angle
	float length;
	float width;
	float height;
};

// ----------------------------
// Obstacle GroundTruth data (SimOne Output) 
// ----------------------------
#define SOSM_OBSTACLE_PREFIX "SOSM_OBSTACLE_"
#define SOSM_OBSTACLE_SIZE_MAX 100

enum SimOne_Obstacle_Type
{
	ESimOne_Obstacle_Type_Unknown = 0,
	ESimOne_Obstacle_Type_Pedestrian = 4,
	ESimOne_Obstacle_Type_Pole = 5,
	ESimOne_Obstacle_Type_Car = 6,
	ESimOne_Obstacle_Type_Static = 7,
	ESimOne_Obstacle_Type_Bicycle = 8,
	ESimOne_Obstacle_Type_Fence = 9,
	ESimOne_Obstacle_Type_RoadMark = 12,
	ESimOne_Obstacle_Type_TrafficSign = 13,
	ESimOne_Obstacle_Type_TrafficLight = 15,
	ESimOne_Obstacle_Type_Rider = 17,
	ESimOne_Obstacle_Type_Truck = 18,
	ESimOne_Obstacle_Type_Bus = 19,
	ESimOne_Obstacle_Type_Train = 20,
	ESimOne_Obstacle_Type_Motorcycle = 21,
	ESimOne_Obstacle_Type_Dynamic = 22,
	ESimOne_Obstacle_Type_GuardRail = 23,
	ESimOne_Obstacle_Type_SpeedLimitSign = 26,
	ESimOne_Obstacle_Type_BicycleStatic = 27,
	ESimOne_Obstacle_Type_RoadObstacle = 29
};

struct SimOne_Data_Obstacle_Entry
{
	int id; // Obstacle global unique ID
	int viewId; // Obstacle view ID in Sim-One observer.
	SimOne_Obstacle_Type type; // Obstacle Type
	float theta; // [deprecated] Please use oriZ for obstacle heading angle instead
	float posX; // Obstacle Position X on Opendrive (by meter), this point is the centroid of the obstacle.
	float posY; // Obstacle Position Y on Opendrive (by meter), this point is the centroid of the obstacle.
	float posZ; // Obstacle Position Z on Opendrive (by meter), this point is the centroid of the obstacle.
	float oriX; // Obstacle Rotation X on Opendrive (by radian)
	float oriY; // Obstacle Rotation Y on Opendrive (by radian)
	float oriZ; // Obstacle Rotation Z on Opendrive (by radian)
	float velX; // Obstacle Velocity X on Opendrive (by meter)
	float velY; // Obstacle Velocity Y on Opendrive (by meter)
	float velZ; // Obstacle Velocity Z on Opendrive (by meter)
	float length; // Obstacle length
	float width; // Obstacle width
	float height; // Obstacle height
};

struct SimOne_Data_Obstacle : public SimOne_Data
{
	int obstacleSize; // Obstacle size
	SimOne_Data_Obstacle_Entry obstacle[SOSM_OBSTACLE_SIZE_MAX]; // Obstacle, 100 max
};



struct SimOne_Data_CaseInfo
{
	char caseName[SOSM_CASENAME_LENGTH];
	char caseId[SOSM_CASEID_LENGT];
	char taskId[SOSM_TASKID_LENGT];
	char sessionId[SOSM_SESSIONID_LENGT];
};
enum SimOne_Case_Status
{
	SimOne_Case_Status_Unknow = 0,
	SimOne_Case_Status_Stop = 1,
	SimOne_Case_Status_Running = 2,
	SimOne_Case_Status_Pause = 3
};

#define SOSM_SIGNAL_LIGHTS_PREFIX "SOSM_SIGNAL_LIGHTS_"
enum SimOne_Signal_Light
{
	ESimOne_Signal_Light_RightBlinker = 1,
	ESimOne_Signal_Light_LeftBlinker = (1 << 1),
	ESimOne_Signal_Light_DoubleFlash = (1 << 2),
	ESimOne_Signal_Light_BrakeLight = (1 << 3),
	ESimOne_Signal_Light_FrontLight = (1 << 4),
	ESimOne_Signal_Light_HighBeam = (1 << 5),
	ESimOne_Signal_Light_BackDrive = (1 << 6)
};
struct SimOne_Data_Signal_Lights : public SimOne_Data
{
	uint32_t signalLights = 0;
};

#define SOSM_ENVIRONMENT "SOSM_ENVIRONMENT"
struct SimOne_Data_Environment
{
	float timeOfDay = 1000;			// time of day [0, 2400]
	float heightAngle = 90;			//	height angle [0, 90]
	float directionalLight = 0.5f;	// light for sun or moon [0, 1]
	float ambientLight = 0.5f;		// ambient light [0, 1]
	float artificialLight = 0.5f;	// artificial light [0, 1]
	float cloudDensity = 0.2f;		// cloud density [0, 1]
	float fogDensity = 0.0f;		// fog density [0, 1]
	float rainDensity = 0.0f;		// rain density [0, 1]
	float snowDensity = 0.0f;		// snow density [0, 1]
	float groundHumidityLevel = 0.1f; // ground humidity level [0, 1]
	float groundDirtyLevel = 0.1f;	// ground dirty level [0, 1]
};

// ----------------------------
// Sensor Configuration API.
// ----------------------------

enum ESimOneNodeType
{
	ESimOneNode_Vehicle = 0,
	ESimOneNode_Camera = 1,
	ESimOneNode_LiDAR = 2,
	ESimOneNode_MMWRadar = 3,
	ESimOneNode_UltrasonicRadar = 4,
	ESimOneNode_AllUltrasonicRadar = 5,
	ESimOneNode_GNSSINS = 6,
	ESimOneNode_PerfectPerception = 7,
	ESimOneNode_V2X = 8,
	ESimOneNode_SensorFusion = 9
};
////enum ESimOneSensorDataType
//{
//	EDataType_Image = 0,
//	EDataType_ScanPointCloud = 1,
//	EDataType_RadarDetections = 2,
//	EDataType_ObstacleDetection = 3,
//	EDataType_UltrasonicRadar = 4,
//	EDataType_GroundTruth = 5,
//
//
//	EDataType_V2X = 6,
//	EDataType_ImageWithGroundTruth = 7,
//	EDataType_PointCloudWithGroundTruth = 8,
//	EDataType_Xviz = 9
//};
enum ESensorDataType
{
	EDataType_ImageWithGroundTruth = 0,
	EDataType_PointCloudWithGroundTruth = 1,
	EDataType_RadarDetections = 2,
	EDataType_UltrasonicRadar = 3,
	EDataType_ObstacleDetection = 4,
	EDataType_GroundTruth = 5,
	EDataType_V2X = 6
};


#define SENSOR_TYPE_MAX_LENGHT 64
struct SimOneSensorConfiguration
{
	int index;
	int mainVehicle;
	int sensorId;
	char sensorType[SENSOR_TYPE_MAX_LENGHT];
	float x;
	float y;
	float z;
	float roll;
	float pitch;
	float yaw;
	int hz;
};

#define SOSM_SENSOR_CONFIGURATION_LABEL "SOSM_SENSOR_CONFIGURATION"
#define SOSM_SENSOR_CONFIGURATION_SIZE_MAX 100
struct SimOne_Data_SensorConfigurations
{
	int dataSize; // data size	
	SimOneSensorConfiguration data[SOSM_SENSOR_CONFIGURATION_SIZE_MAX];
};

// ----------------------------
// Sensor Detections data (SimOne Output) 
// ----------------------------
#define SOSM_SENSOR_DETECTIONS_PREFIX "SOSM_SENSOR_DETECTIONS_"
#define SOSM_SENSOR_DETECTIONS_OBJECT_SIZE_MAX 256
#define SOSM_SENSOR_LANE_OBJECT_SIZE_MAX 256
#define SOSM_SENSOR_Boundary_OBJECT_SIZE_MAX 80
struct SimOne_Data_SensorDetections_Entry
{
	int id;					// Detection Object ID
	SimOne_Obstacle_Type type;	// Detection Object Type
	float posX;				// Detection Object Position X in meter
	float posY;				// Detection Object Position Y in meter
	float posZ;				// Detection Object Position Z in meter
	float oriX;				// Rotation X in radian
	float oriY;				// Rotation Y in radian
	float oriZ;				// Rotation Z in radian
	float length;			// Detection Object Length in meter
	float width;			// Detection Object Width in meter
	float height;			// Detection Object Height in meter
	float range;			// Detection Object relative range in meter
	float velX;				// Detection Object Velocity X
	float velY;				// Detection Object Velocity Y
	float velZ;				// Detection Object Velocity Z
	float probability;		// Detection probability
	float relativePosX;		// Relative position X in sensor space
	float relativePosY;		// Relative position Y in sensor space
	float relativePosZ;		// Relative position Z in sensor space
	float relativeRotX;		// Relative rotation X in sensor space
	float relativeRotY;		// Relative rotation Y in sensor space
	float relativeRotZ;		// Relative rotation Z in sensor space
	float relativeVelX;		// Relative velocity X in sensor space
	float relativeVelY;		// Relative velocity Y in sensor space
	float relativeVelZ;		// Relative velocity Z in sensor space
	float bbox2dMinX = 0;	// bbox2d minX in pixel if have
	float bbox2dMinY = 0;	// bbox2d minY in pixel if have
	float bbox2dMaxX = 0;	// bbox2d maxX in pixel if have
	float bbox2dMaxY = 0;	// bbox2d maxY in pixel if have
};

struct SimOne_Data_SensorDetections : public SimOne_Data
{
	int objectSize; // Detection Object size
	SimOne_Data_SensorDetections_Entry objects[SOSM_SENSOR_DETECTIONS_OBJECT_SIZE_MAX]; // Detection Objects, 256 max
};

struct SimOne_Data_SensorFusionObstacles : public SimOne_Data
{
	int obstacleSize;
	SimOne_Data_SensorDetections_Entry obstacle[SOSM_SENSOR_DETECTIONS_OBJECT_SIZE_MAX];
};

enum ESimOneLaneType {
	LaneType_none = 0,
	LaneType_driving = 1,
	LaneType_stop = 2,
	LaneType_shoulder = 3,
	LaneType_biking = 4,
	LaneType_sidewalk = 5,
	LaneType_border = 6,
	LaneType_restricted = 7,
	LaneType_parking = 8,
	LaneType_bidirectional = 9,
	LaneType_median = 10,
	LaneType_special1 = 11,
	LaneType_special2 = 12,
	LaneType_special3 = 13,
	LaneType_roadWorks = 14,
	LaneType_tram = 15,
	LaneType_rail = 16,
	LaneType_entry = 17,
	LaneType_exit = 18,
	LaneType_offRamp = 19,
	LaneType_onRamp = 20,
	LaneType_mwyEntry = 21,
	LaneType_mwyExit = 22
};



enum ESimOneData_BoundaryType {
	BoundaryType_none = 0,
	BoundaryType_solid = 1,
	BoundaryType_broken = 2,
	BoundaryType_solid_solid = 3,
	BoundaryType_solid_broken = 4,
	BoundaryType_broken_solid = 5,
	BoundaryType_broken_broken = 6,
	BoundaryType_botts_dots = 7,
	BoundaryType_grass = 8,
	BoundaryType_curb = 9
};
enum ESimOneData_BoundaryColor {
	BoundaryColor_standard = 0,
	BoundaryColor_blue = 1,
	BoundaryColor_green = 2,
	BoundaryColor_red = 3,
	BoundaryColor_white = 4,
	BoundaryColor_yellow = 5
};
struct ESimOneData_LineCurveParameter{
	float C0;
	float C1;
	float C2;
	float C3;
	SimOneData_Vec3f firstPoints;
	SimOneData_Vec3f endPoints;
	float length = 7;
};
struct SimOne_Data_LaneLineInfo 
{
	int lineID;
	ESimOneData_BoundaryType lineType;//laneline BoundaryType
	ESimOneData_BoundaryColor lineColor;//laneline BoundaryColor
	float linewidth;//laneline width
	SimOneData_Vec3f linePoints[SOSM_SENSOR_Boundary_OBJECT_SIZE_MAX];//total laneline Boundary points ,MaX 80
	ESimOneData_LineCurveParameter linecurveParameter;//laneline boundary curveParameter

};
struct SimOne_Data_LaneInfo :public SimOne_Data
{
	int id = 0;//Lane ID 
	ESimOneLaneType laneType;//Lane type
	int laneLeftID = 0;//The Lane's leftLane ID  
	int laneRightID = 0;//The Lane's rightLane ID 
	int lanePredecessorID[SOSM_SENSOR_LANE_OBJECT_SIZE_MAX];//total of lane predecessor ID,max 256
	int laneSuccessorID[SOSM_SENSOR_LANE_OBJECT_SIZE_MAX];//total of lane successor ID,max 256
	SimOne_Data_LaneLineInfo l_Line;//lane left lineBoundary;
	SimOne_Data_LaneLineInfo c_Line;//lane center lineBoundary;
	SimOne_Data_LaneLineInfo r_Line;//lane right lineBoundary;
	SimOne_Data_LaneLineInfo ll_Line;//laneleft left lineBoundary;
	SimOne_Data_LaneLineInfo rr_Line;//laneright right lineBoundary;
	
};


// ----------------------------
// OSI GroundTruth Data (SimOne Output) 
// ----------------------------
#define SOSM_GROUNDTRUTH_OSI_PREFIX "SOSM_GROUNDTRUTH_OSI_"
#define SOSM_SENSORDATA_OSI_PREFIX "SOSM_SENSORDATA_OSI_"
#define SOSM_OSI_DATA_SIZE_MAX 1024*1024*8

struct SimOne_Data_OSI : public SimOne_Data
{
	int dataSize; // data size	
	char data[SOSM_OSI_DATA_SIZE_MAX];
};

enum SimOne_ClientType {
	ESimOneClientType_None = 0,
	ESimOneClientType_Web = 1,
	ESimOneClientType_TrafficProvider = 2,
	ESimOneClientType_VehicleDynamic = 3,
	ESimOneClientType_BridgeIO = 4,
	ESimOneClientType_SimOneDLL = 5,
	ESimOneClientType_Observer = 6,
	ESimOneClientType_Sensor = 7,
	ESimOneClientType_Traffic = 8,
};
// ----------------------------
// Image data (SimOne Output) 
// ----------------------------
#define SOSM_IMAGE_PREFIX "SOSM_IMAGE_"
//#define SOSM_IMAGE_WIDTH_MAX 1920
//#define SOSM_IMAGE_HEIGHT_MAX 1200
#define SOSM_IMAGE_WIDTH_MAX 3840
#define SOSM_IMAGE_HEIGHT_MAX 2160
#define SOSM_IMAGE_DATA_SIZE_MAX SOSM_IMAGE_WIDTH_MAX*SOSM_IMAGE_HEIGHT_MAX*3
enum SimOne_Image_Format
{
	ESimOne_Image_Format_RGB = 0
};

struct SimOne_Data_Image : public SimOne_Data
{
	int width; // Image resolution width 1920 max
	int height; // Image resolution height 1200 max
	SimOne_Image_Format format; // Image format, RGB only for now
	int imageDataSize; // image data size	
	char imageData[SOSM_IMAGE_DATA_SIZE_MAX]; // 1920 x 1200 x 3 max
};


// ----------------------------
// Point cloud data (SimOne Output) 
// ----------------------------
#define SOSM_POINT_CLOUD_PREFIX "SOSM_POINT_CLOUD_"
#define SOSM_POINT_DATA_SIZE_MAX 3686400 // Max Memory Size
struct SimOne_Data_Point_Cloud : public SimOne_Data
{
	int width;
	int height;
	int pointStep;
	int pointCloudDataSize;
	char pointCloudData[SOSM_POINT_DATA_SIZE_MAX];
};

// ----------------------------
// Millimeter-wave Radar data (SimOne Output) 
// ----------------------------
#define SOSM_RADAR_PREFIX "SOSM_RADAR_"
#define SOSM_RADAR_SIZE_MAX 256

struct SimOne_Data_RadarDetection_Entry {
	int id;					// Detection Object ID
	int subId;				// Detection Object Sub ID
	SimOne_Obstacle_Type type;	// Detection Object Type
	float posX;				// Detection Object Position X in meter
	float posY;				// Detection Object Position Y in meter
	float posZ;				// Detection Object Position Z in meter
	float velX;				// Detection Object Velocity X
	float velY;				// Detection Object Velocity Y
	float velZ;				// Detection Object Velocity Z
	float range;			// Detection Object relative range in meter
	float rangeRate;		// Detection Object relative range rate in m/s
	float azimuth;			// Detection Object azimuth angle
	float vertical;			// Detection Object vertical angle
	float snrdb;			// Signal noise ratio
	float rcsdb;			// Detection Object RCS
	float probability;		// Detection probability
};

struct SimOne_Data_RadarDetection : public SimOne_Data
{
	int detectNum;												// Detection Object number
	SimOne_Data_RadarDetection_Entry detections[SOSM_RADAR_SIZE_MAX];	// Detection Objects, 256 max
};

// ----------------------------
// Ultrasonic Radar data (SimOne Output) 
// ----------------------------
#define SOSM_MUCHULTRASONICRADAR_PREFIX "SOSM_MUCHULTRASONICRADAR_"
#define SOSM_OSIULTRASONICRADAR_PREFIX "SOSM_OSIULTRASONICRADAR_"
#define SOSM_OBSTACL_SIZE_MAX 100
#define SOSM_ULTRASONICRADAR_SIZE_MAX 100


struct SimOne_Data_UltrasonicRadarDetection_Entry{
	float obstacleRanges = 0;
	float x = 0;
	float y = 0;
};
struct SimOne_Data_UltrasonicRadar : public SimOne_Data {
	int id;//UltrasonicRadar's ID
	int obstacleNum;	// Obstacle Range number
	SimOne_Data_UltrasonicRadarDetection_Entry obstacledetections[SOSM_OBSTACL_SIZE_MAX];
};

struct SimOne_Data_UltrasonicRadars : public SimOne_Data
{
	int UltrasonicRadarsNum;													// Detection number
	SimOne_Data_UltrasonicRadar ultrasonicRadars[SOSM_ULTRASONICRADAR_SIZE_MAX];	// Detection, 100 max
};

#ifndef WITHOUT_HDMAP
// ----------------------------
// V2X BSM data (SimOne Output) 
// ----------------------------
#define SOSM_V2XBSM_PREFIX "SOSM_V2XBSM_"
#define SOSM_V2X_SIZE_MAX 256

typedef V2X::m_BasicSafetyMessage SimOne_Data_V2XBSM_Entry;

struct SimOne_Data_V2XBSM : public SimOne_Data
{
	time_t timestamp;
	SSD::SimVector<SimOne_Data_V2XBSM_Entry> detections;
};


// ----------------------------
// V2X RSI data (SimOne Output) 
// ----------------------------
#define SOSM_V2XRSI_PREFIX "SOSM_V2XRSI_"

typedef V2X::m_RoadSideInformation SimOne_Data_V2XRSI_Entry;

struct SimOne_Data_V2XRSI : public SimOne_Data
{
	time_t timestamp;												// Detection Object number
	SSD::SimVector <SimOne_Data_V2XRSI_Entry> detections;	    // Detection Objects, 256 max
};


// ----------------------------
// V2X RSM data (SimOne Output) 
// ----------------------------
#define SOSM_V2XRSM_PREFIX "SOSM_V2XRSM_"

typedef V2X::m_BasicSafetyMessage SimOne_Data_V2XRSM_Entry;

struct SimOne_Data_V2XRSM : public SimOne_Data
{
	time_t timestamp;											// Detection Object number
	SSD::SimVector <SimOne_Data_V2XRSM_Entry> detections;	    // Detection Objects, 256 max
};

// ----------------------------
// V2X SPAT data (SimOne Output) 
// ----------------------------
#define SOSM_V2XSPAT_PREFIX "SOSM_V2XSPAT_"

typedef V2X::m_SPAT SimOne_Data_V2XSPAT_Entry;

struct SimOne_Data_V2XSPAT : public SimOne_Data
{
	time_t timestamp;											// Detection Object number
	SSD::SimVector<SimOne_Data_V2XSPAT_Entry> detections;	    // Detection Objects, 256 max
};

// ----------------------------
// V2X MAP data (SimOne Output) 
// ----------------------------
#define SOSM_V2XMAP_PREFIX "SOSM_V2XMAP_"

typedef V2X::m_MapData SimOne_Data_V2XMAP_Entry;

struct SimOne_Data_V2XMAP : public SimOne_Data
{
	time_t timestamp;											// Detection Object number
	SSD::SimVector <SimOne_Data_V2XMAP_Entry> detections;	    // Detection Objects, 256 max
};

struct SimOne_Data_V2X:public SimOne_Data
{
	SimOne_Data_V2XBSM bsmData;
	SimOne_Data_V2XRSI rsiData;
	SimOne_Data_V2XRSM rsmData;
	SimOne_Data_V2XSPAT spatData;
	SimOne_Data_V2XMAP mapData;
};
#endif

// ----------------------------
// HDMap data
// ----------------------------

// ----------------------------
// Prediction data (SimOne Output) 
// ----------------------------
#define SOSM_PREDICTION_PREFIX "SOSM_PREDICTION_"
struct SimOne_Data_Traffic_Info
{
	int id;
	float x;
	float y;
	float speed;
	float orientation;
};

struct SimOne_Data_Position_Info : public SimOne_Data
{
	float mean_x;
	float mean_y;
	float var_x;
	float var_y;
	float covar_xy;
};

struct SimOne_Data_Prediction : public SimOne_Data
{
	std::map<int, std::vector<SimOne_Data_Position_Info>> ped_predictions;
	std::map<int, std::vector<SimOne_Data_Position_Info>> veh_predictions;
	float ped_delta_t;
	float veh_delta_t;
};
#define MAX_MAINVEHICLE_NUM 10
#define MAX_MAINVEHICLE_NAME_LEN 64
struct SimOne_Data_MainVehicle_Info
{
	int size;
	int id_list[MAX_MAINVEHICLE_NUM];
	char type_list[MAX_MAINVEHICLE_NUM][MAX_MAINVEHICLE_NAME_LEN];
};

struct SimOne_Data_MainVehicle_Status
{
	int mainVehicleId;
	int mainVehicleStatus;
};

// ----------------------------
// TrafficLight data (SimOne Output) 
// ----------------------------
#define SOSM_TRAFFICLIGHT_PREFIX "SOSM_TRAFFICLIGHT_"
#define SOSM_TRAFFICLIGHT_SIZE_MAX 100

enum SimOne_TrafficLight_Status
{
	ESimOne_TrafficLight_Status_Invalid = 0,
	ESimOne_TrafficLight_Status_Red = 1,
	ESimOne_TrafficLight_Status_Green = 2,
	ESimOne_TrafficLight_Status_Yellow = 3,
	ESimOne_TrafficLight_Status_RedBlink = 4,
	ESimOne_TrafficLight_Status_GreenBlink = 5,
	ESimOne_TrafficLight_Status_YellowBlink = 6,
	ESimOne_TrafficLight_Status_Black = 7
};

struct SimOne_Data_TrafficLight
{
	int index;
	int opendriveLightId;
	int countDown;
	SimOne_TrafficLight_Status status;
};

struct SimOne_Data_TrafficLights : public SimOne_Data
{
	int trafficlightNum;	// Obstacle number
	SimOne_Data_TrafficLight trafficlights[SOSM_TRAFFICLIGHT_SIZE_MAX];	// Obstacle, 100 max
};

// ----------------------------
// SimOneDriver status data (SimOne Output) 
// ----------------------------
#define SOSM_DRIVER_PREFIX "SOSM_DRIVER_"

enum SimOne_Driver_Status
{
	ESimOne_Driver_Status_Unknown = 0,
	ESimOne_Driver_Status_Controlling = 1,
	ESimOne_Driver_Status_Disabled = 2
};

struct SimOne_Data_Driver_Status : public SimOne_Data
{
	SimOne_Driver_Status driverStatus;
};

// ----------------------------
// Scenario event
// ----------------------------
#define ENABLE_SCENARIO_EVENT
#define SCENARIO_EVENT_PREFIX "SCENARIO_EVENT_"

struct SimOneScenarioEventReaderStatus
{
	int readerState = 0;
};

struct SimOneScenarioEventWriterStatus
{
	int writeState = 0;
};

struct SimOneScenarioEvent : public SimOneScenarioEventWriterStatus
{
	char event[64];
	char data[64];
};
#pragma pack(pop)