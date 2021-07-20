# -*- coding: utf-8 -*-
#
# Created By: Huiyong.Men 2019/11/08
#
#-----------------------------------------------------
# ***Warning*** This file MUST match SimOneIOStruct.h
#-----------------------------------------------------
from ctypes import *
import os
import platform

global HDMapModule, SimoneIOAPI, SimoneIOAPI_dll,SimoneStreamingIOAPI,SimOneStreamingIOAPI_dll

sys = platform.system()
if sys == "Windows":
	HDMapModule = "HDMapModule.dll"
	SimoneIOAPI_dll = "SimOneIOAPI.dll"
	SimoneStreamingIOAPI_dll = "SimOneStreamingIOAPI.dll"

elif sys == "Linux":
	HDMapModule = "libHDMapModule.so"
	SimoneIOAPI_dll = "libSimOneIOAPI.so"
	SimoneStreamingIOAPI_dll = "libSimOneStreamingIOAPI.so"


SimOneLibPaths = [
"",
"../Build/build/bin/debug/",
"Win64/",
"../Build/build_debug/bin/debug/"
]

# Append full paths
SimOneLibFullPaths = []
SimOneIOStructRoot = os.getcwd()
for path in SimOneLibPaths:
	SimOneLibFullPaths.append(SimOneIOStructRoot+"/"+path)
SimOneLibPaths += SimOneLibFullPaths

LoadDllSuccess = False
for path in SimOneLibPaths:
	if(LoadDllSuccess == True):
		break
	try:# python v3.8+
		CDLL(path+HDMapModule, winmode=DEFAULT_MODE)
		SimoneIOAPI = CDLL(path + SimoneIOAPI_dll, winmode=DEFAULT_MODE)
		SimoneStreamingIOAPI = CDLL(path + SimoneStreamingIOAPI_dll, winmode=DEFAULT_MODE)
		LoadDllSuccess = True
	except Exception as e:
		pass
		# print(e)

	if LoadDllSuccess:
		print("load libary sucessful")
		break
	try:
		# python 2.7 - 3.7
		CDLL(path+HDMapModule)
		SimoneIOAPI = CDLL(path + SimoneIOAPI_dll)
		SimoneStreamingIOAPI = CDLL(path + SimoneStreamingIOAPI_dll)
		LoadDllSuccess = True
	except Exception as e:
		pass
		# print(e)


if LoadDllSuccess == False:
	print("[SimOne API ERROR] Load SimOneIOAPI.dll/ or.so failed. unable to start")

#print(SimoneStreamingIOAPI)
MAX_MAINVEHICLE_NUM = 10
MAX_MAINVEHICLE_NAME_LEN = 64
TOTAL_LEN = 640


class SimOne_Data_MainVehicle_Info(Structure):
	_fields_ = [
		('size', c_int),
		('id_list', c_int*MAX_MAINVEHICLE_NUM),
		('type_list', c_char*MAX_MAINVEHICLE_NAME_LEN*MAX_MAINVEHICLE_NUM)]


class SimOne_Data_MainVehicle_Status(Structure):
	_fields_ = [
		('mainVehicleId', c_int),
		('mainVehicleStatus', c_int)]


SOSM_CASENAME_LENGT = 256
SOSM_CASEID_LENGT = 256
SOSM_TASKID_LENGT = 256
SOSM_SESSIONID_LENGT = 256
SOSM_EXTRA_STATES_SIZE_MAX = 256

SimOne_Case_Status_Unknow = 0,
SimOne_Case_Status_Stop = 1,
SimOne_Case_Status_Running = 2
SimOne_Case_Status_Pause = 3

class SimOne_Data_CaseInfo(Structure):
	_pack_ = 1
	_fields_ = [
		('caseName', c_char*SOSM_CASENAME_LENGT),
		('caseId', c_char*SOSM_CASEID_LENGT),
		('taskId', c_char*SOSM_TASKID_LENGT),
		('sessionId', c_char*SOSM_SESSIONID_LENGT)]


class SimOne_Data(Structure):
	_pack_ = 1
	_fields_ = [
	('timestamp', c_longlong),
	('frame', c_int),
	('version', c_int)]
	

class SimOne_TrafficLight_Status(c_int):
	ESimOne_TrafficLight_Status_Invalid = 0,
	ESimOne_TrafficLight_Status_Red = 1,
	ESimOne_TrafficLight_Status_Green = 2,
	ESimOne_TrafficLight_Status_Yellow = 3,
	ESimOne_TrafficLight_Status_RedBlink = 4,
	ESimOne_TrafficLight_Status_GreenBlink = 5,
	ESimOne_TrafficLight_Status_YellowBlink = 6,
	ESimOne_TrafficLight_Status_Black = 7

class SimOne_Data_Vehicle_State(c_int):
    ESimOne_X_L1 = 0,
    ESimOne_Y_L1 = 1,
    ESimOne_Z_L1 = 2,
    ESimOne_X_L2 = 3,
    ESimOne_Y_L2 = 4,
    ESimOne_Z_L2 = 5,
    ESimOne_X_R1 = 6,
    ESimOne_Y_R1 = 7,
    ESimOne_Z_R1 = 8,
    ESimOne_X_R2 = 9,
    ESimOne_Y_R2 = 10,
    ESimOne_Z_R2 = 11

SOSM_TRAFFICLIGHT_SIZE_MAX = 100


class SimOne_Data_TrafficLight(Structure):
	_pack_ = 1
	_fields_ = [
	('index', c_int),
	('opendriveLightId', c_int),
	('countDown', c_int),
	('status', SimOne_TrafficLight_Status)
	]


class SimOne_Data_TrafficLights(SimOne_Data):
	_pack_ = 1
	_fields_ = [
		('trafficlightNum', c_int),
		('trafficlights', SimOne_Data_TrafficLight*SOSM_TRAFFICLIGHT_SIZE_MAX)]


class SimOne_Signal_Light(c_int):
	ESimOne_Signal_Light_RightBlinker = 1
	ESimOne_Signal_Light_LeftBlinker = (1 << 1)
	ESimOne_Signal_Light_DoubleFlash = (1 << 2)
	ESimOne_Signal_Light_BrakeLight = (1 << 3)
	ESimOne_Signal_Light_FrontLight = (1 << 4)
	ESimOne_Signal_Light_HighBeam = (1 << 5)
	ESimOne_Signal_Light_BackDrive = (1 << 6)


class SimOne_Data_Signal_Lights(SimOne_Data):
	_pack_ = 1
	_fields_ = [
		('signalLights', c_uint)]


class SimOne_Data_Pose_Control(SimOne_Data):
	_pack_ = 1
	_fields_ = [
	('posX', c_float),
	('posY', c_float),
	('posZ', c_float),
	('oriX', c_float),
	('oriY', c_float),
	('oriZ', c_float),
	('autoZ', c_bool)]


class EGearMode(c_int):
	EGearMode_Neutral = 0
	EGearMode_Drive = 1      # forward gear for automatic gear
	EGearMode_Reverse = 2
	EGearMode_Parking = 3

	EGearManualMode_1 = 4    # forward gear 1 for manual gear
	EGearManualMode_2 = 5
	EGearManualMode_3 = 6
	EGearManualMode_4 = 7
	EGearManualMode_5 = 8
	EGearManualMode_6 = 9
	EGearManualMode_7 = 10
	EGearManualMode_8 = 11

class EThrottleMode(c_int):
    EThrottleMode_Percent = 0         # [0, 1]
    EThrottleMode_Torque = 1          # engine torque, N.m
    EThrottleMode_Speed = 2           # vehicle speed, m/s,   in this mode, brake input is ignored
    EThrottleMode_Accel = 3           # vehicle acceleration, m/s^2, in this mode, brake input is ignored
    EThrottleMode_EngineAV = 4        # engine, rpm
    EThrottleMode_WheelTorque = 5      # torques applied to each wheel, array, size is the wheel number, N.m

class EBrakeMode(c_int):
    EBrakeMode_Percent = 0
    EBrakeMode_MasterCylinderPressure = 1 # degree
    EBrakeMode_PedalForce = 2
    EBrakeMode_WheelCylinderPressure = 3   # Mpa for each wheel
    EBrakeMode_WheelTorque = 4             # Nm for each wheel
#
class ESteeringMode(c_int):
    ESteeringMode_Percent = 0
    ESteeringMode_SteeringWheelAngle = 1
    ESteeringMode_Torque = 2
    ESteeringAngularSpeed = 3            # steering wheel angualr speed, degree/s
    ESteeringWheelAngle = 4              # degree for each wheel
    ESteeringWheelAnglarSpeed = 5        # degree/s for each wheel

class ELogLevel_Type(c_int):
	ELogLevel_Debug = 0
	ELogLevel_Information = 1
	ELogLevel_Warning = 2
	ELogLevel_Error = 3
	ELogLevel_Fatal = 4

SOSM_MAX_WHEEL_NUM = 20
class SimOne_Data_Control(SimOne_Data):
	_pack_ = 1
	_fields_ = [
    ('EThrottleMode', EThrottleMode),
	('throttle', c_float),
	('EBrakeMode', EBrakeMode),
	('brake', c_float),
	('ESteeringMode', ESteeringMode),
	('steering', c_float),
	('handbrake', c_bool),
	('isManualGear', c_bool),
	('gear', EGearMode), # 0: Neutral; 1: Drive; 2: Reverse; 3: Parking
    ('clutch', c_float),
    ('throttle_input_data', c_float * SOSM_MAX_WHEEL_NUM),
    ('brake_input_data', c_float * SOSM_MAX_WHEEL_NUM),
    ('steering_input_data', c_float * SOSM_MAX_WHEEL_NUM)]

class SimOne_Data_ESP_Control(SimOne_Data):
	_pack_ = 1
	_fields_ = [
	('stopDistance', c_int),
	('velocityLimit', c_float),
	('steering', c_float),
	('steerTorque', c_float),
	('accel', c_float),
	('accelUpperLimit', c_float),
	('accelLowerLimit', c_float),
	('accelUpperComfLimit', c_float),
	('accelLowerComfLimit', c_float),
	('standStill', c_bool),
	('driveOff', c_bool),
	('brakeMode', c_int),
	('vlcShutdown', c_int),
	('gearMode', c_int)]

class ESimone_Vehicle_EventInfo_Type(c_int):
	ESimOne_VehicleEventInfo_Forward_Collision = 0
	ESimOne_VehicleEventInfo_Backward_Collision = 1
	ESimOne_VehicleEventInfo_Left_Turn = 2
	ESimOne_VehicleEventInfo_Right_Turn = 3
	ESimOne_VehicleEventInfo_Forward_Straight = 4
	ESimOne_VehicleEventInfo_Over_Speed = 5


class SimOne_Data_Vehicle_EventInfo(SimOne_Data):
	_pack_ = 1
	_fields_ = [
	('type', ESimone_Vehicle_EventInfo_Type)]


SOSM_TRAJECTORY_SIZE_MAX = 100


class SimOne_Data_Trajectory_Entry(Structure):
	_pack_ = 1
	_fields_ = [
	('posX', c_float), # Trajectory Position X no Opendrive (by meter)
	('posY', c_float), # Trajectory Position Y no Opendrive (by meter)
	('vel', c_float)]  # Velocity (by meter/second)
	

class SimOne_Data_Trajectory(SimOne_Data):
	_pack_ = 1
	_fields_ = [
	('trajectorySize', c_int),
	('trajectory', SimOne_Data_Trajectory_Entry * SOSM_TRAJECTORY_SIZE_MAX)]
	
class SimOne_Data_Gps(SimOne_Data):
	_pack_ = 1
	_fields_ = [
	('posX', c_float), # Position X no Opendrive (by meter)
	('posY', c_float), # Position Y no Opendrive (by meter)
	('posZ', c_float), # Position Z no Opendrive (by meter)
	('oriX', c_float), # Rotation X no Opendrive (by radian)
	('oriY', c_float), # Rotation Y no Opendrive (by radian)
	('oriZ', c_float), # Rotation Z no Opendrive (by radian)
	('velX', c_float), # MainVehicle Velocity X on Opendrive (by meter)
	('velY', c_float), # MainVehicle Velocity Y on Opendrive (by meter)
	('velZ', c_float), # MainVehicle Velocity Z on Opendrive (by meter)
	('throttle', c_float), #MainVehicle Throttle
	('brake', c_float), #MainVehicle brake
	('steering', c_float), #MainVehicle Steering angle
	('gear', c_int), # MainVehicle gear position
	('accelX', c_float), # MainVehilce Acceleration X on Opendrive (by meter)
	('accelY', c_float), # MainVehilce Acceleration Y on Opendrive (by meter)
	('accelZ', c_float), # MainVehilce Acceleration Z on Opendrive (by meter)
	('angVelX', c_float), # MainVehilce Angular Velocity X on Opendrive (by meter)
	('angVelY', c_float), # MainVehilce Angular Velocity Y on Opendrive (by meter)
	('angVelZ', c_float), # MainVehilce Angular Velocity Z on Opendrive (by meter)
	('wheelSpeedFL', c_float), # Speed of front left wheel (by meter/sec)
	('wheelSpeedFR', c_float), # Speed of front right wheel (by meter/sec)
	('wheelSpeedRL', c_float), # Speed of rear left wheel (by meter/sec)
	('wheelSpeedRR', c_float), # Speed of rear right wheel (by meter/sec)
	('engineRpm', c_float), # Speed of engine (by r/min)
	('odometer', c_float),#  odometer in meter.
	('extraStates', c_float*SOSM_EXTRA_STATES_SIZE_MAX),# vehicle states subscripted by MainVehicleExtraDataIndics message
	('extraStateSize', c_int)]


SOSM_OBSTACLE_SIZE_MAX = 100


class SimOne_Obstacle_Type(c_int):
	ESimOne_Obstacle_Type_Unknown = 0
	ESimOne_Obstacle_Type_Pedestrian = 4
	ESimOne_Obstacle_Type_Pole = 5
	ESimOne_Obstacle_Type_Car = 6
	ESimOne_Obstacle_Type_Static = 7
	ESimOne_Obstacle_Type_Bicycle = 8
	ESimOne_Obstacle_Type_Fence = 9
	ESimOne_Obstacle_Type_RoadMark = 12
	ESimOne_Obstacle_Type_TrafficSign = 13
	ESimOne_Obstacle_Type_TrafficLight = 15
	ESimOne_Obstacle_Type_Rider = 17
	ESimOne_Obstacle_Type_Truck = 18
	ESimOne_Obstacle_Type_Bus = 19
	ESimOne_Obstacle_Type_SpecialVehicle = 20
	ESimOne_Obstacle_Type_Motorcycle = 21
	ESimOne_Obstacle_Type_Dynamic = 22
	ESimOne_Obstacle_Type_GuardRail = 23
	ESimOne_Obstacle_Type_SpeedLimitSign = 26
	ESimOne_Obstacle_Type_BicycleStatic = 27
	ESimOne_Obstacle_Type_RoadObstacle = 29


class SimOne_Data_Obstacle_Entry(Structure):
	_pack_ = 1
	_fields_ = [
	('id', c_int), # Obstacle ID
	('viewId', c_int),  # Obstacle ID
	('type', SimOne_Obstacle_Type), # Obstacle Type
	('theta', c_float), # Obstacle vertical rotation (by radian)
	('posX', c_float), # Obstacle Position X no Opendrive (by meter)
	('posY', c_float), # Obstacle Position Y no Opendrive (by meter)
	('posZ', c_float), # Obstacle Position Z no Opendrive (by meter)
	('oriX', c_float), # Obstacle Velocity X no Opendrive (by meter)
	('oriY', c_float), # Obstacle Velocity Y no Opendrive (by meter)
	('oriZ', c_float), # Obstacle Velocity Z no Opendrive (by meter)
	('velX', c_float), # Obstacle Velocity X no Opendrive (by meter)
	('velY', c_float), # Obstacle Velocity Y no Opendrive (by meter)
	('velZ', c_float), # Obstacle Velocity Z no Opendrive (by meter)
	('length', c_float), # Obstacle length
	('width', c_float), # Obstacle width
	('height', c_float)] # Obstacle height


class SimOne_Data_Obstacle(SimOne_Data):
	_pack_ = 1
	_fields_ = [
	('obstacleSize', c_int), # Obstacle Size
	('obstacle', SimOne_Data_Obstacle_Entry*SOSM_OBSTACLE_SIZE_MAX)] # Obstacles

SOSM_IMAGE_WIDTH_MAX = 3840
SOSM_IMAGE_HEIGHT_MAX = 2160
SOSM_IMAGE_DATA_SIZE_MAX = SOSM_IMAGE_WIDTH_MAX*SOSM_IMAGE_HEIGHT_MAX*3


class ESimOneNodeType(c_int):
	ESimOneNode_Vehicle = 0
	ESimOneNode_Camera = 1
	ESimOneNode_LiDAR = 2
	ESimOneNode_MMWRadar = 3
	ESimOneNode_UltrasonicRadar = 4
	ESimOneNode_AllUltrasonicRadar = 5
	ESimOneNode_GNSSINS = 6
	ESimOneNode_PerfectPerception = 7
	ESimOneNode_V2X = 8

SENSOR_TYPE_MAX_LENGHT = 64
class SimOneSensorConfiguration(Structure):
	_pack_ = 1
	_fields_ = [
	('index', c_int),
	('mainVehicle', c_int), # 
	('sensorId', c_int), # Sensor's ID
	('sensorType', c_char * SENSOR_TYPE_MAX_LENGHT),# Sensor's ESimOneNodeType
	('x', c_float),# Obstacle Position X no Opendrive (by meter)
	('y', c_float),# Obstacle Position Y no Opendrive (by meter)
	('z', c_float),# Obstacle Position Z no Opendrive (by meter)
	('roll', c_float),# Sensor's Rotation coordinates in x
	('pitch', c_float),# Sensor's Rotation coordinates in y
	('yaw', c_float),# Sensor's Rotation coordinates in z
	('hz', c_int)]#Sensor's frequency


SOSM_SENSOR_CONFIGURATION_SIZE_MAX = 100


class SimOneSensorConfigurations(Structure):
	_pack_ = 1
	_fields_ =[
		('dataSize', c_int),  # num of Sensors
		('data', SimOneSensorConfiguration*SOSM_SENSOR_CONFIGURATION_SIZE_MAX)
	]


class SimOne_Image_Format(c_int):
	ESimOne_Image_Format_RGB = 0


class SimOne_Data_Image(SimOne_Data):
	_pack_ = 1
	_fields_ = [
	('width', c_int), # Image resolution width 1920 max
	('height', c_int), # Image resolution height 1080 max
	('format', SimOne_Image_Format), # Image format. 0: RGB
	('imagedataSize', c_int), # Image data size
	('imagedata', c_char * SOSM_IMAGE_DATA_SIZE_MAX)] #1920 x 1080 x 3 max


SOSM_POINT_DATA_SIZE_MAX = 64*57600


class SimOne_Data_Point_Cloud(SimOne_Data):
	_pack_ = 1
	_fields_ = [
	('width', c_int),
	('height', c_int),
	('pointStep', c_int),
	('pointCloudDataSize', c_int),
	('pointClouddata', c_char * SOSM_POINT_DATA_SIZE_MAX)]


SOSM_RADAR_SIZE_MAX = 256


class SimOne_Data_RadarDetection_Entry(Structure):
	_pack_ = 1
	_fields_ = [
	('id', c_int),				# Obstacle ID
	('subId', c_int),			# Obstacle Sub ID
	('type', c_int),			# Obstacle Type
	('posX', c_float),			# Obstacle Position X no Opendrive (by meter)
	('posY', c_float),			# Obstacle Position Y no Opendrive (by meter)
	('posZ', c_float),			# Obstacle Position Z no Opendrive (by meter)
	('velX', c_float),			# Obstacle Velocity X no Opendrive (by meter)
	('velY', c_float),			# Obstacle Velocity Y no Opendrive (by meter)
	('velZ', c_float),			# Obstacle Velocity Z no Opendrive (by meter)
	('range', c_float),			# Obstacle relative range in meter 
	('rangeRate', c_float),		# Obstacle relative range rate in m/s
	('azimuth', c_float),		# Obstacle azimuth angle
	('vertical', c_float),		# Obstacle vertical angle
	('snrdb', c_float),			# Signal noise ratio
	('rcsdb', c_float),			# Obstacle RCS
	('probability', c_float)]	# detection probability


class SimOne_Data_RadarDetection(SimOne_Data):
	_pack_ = 1
	_fields_ = [
	('detectNum', c_int), # Obstacle Size
	('detections', SimOne_Data_RadarDetection_Entry*SOSM_RADAR_SIZE_MAX)] # Obstacles
	

SOSM_OBSTACL_SIZE_MAX = 100


class SimOne_Data_UltrasonicRadarDetection_Entry(Structure):
	_pack_ = 1
	_fields_ = [
		('obstacleRanges', c_float),  # Obstacle from Ultrasonic distance
		('x', c_float),  # Obstacle relativelX
		('y', c_float) # Obstacle relativelY
		]

class SimOne_Data_UltrasonicRadar(SimOne_Data):
	_pack_ = 1
	_fields_ = [
		('id', c_int),  # Ultrasonic ID
		('obstacleNum', c_int),  # Ultrasonic detect object nums
		('obstacledetections', SimOne_Data_UltrasonicRadarDetection_Entry * SOSM_OBSTACL_SIZE_MAX) # object information
		]


SOSM_ULTRASONICRADAR_SIZE_MAX = 100


class SimOne_Data_UltrasonicRadars(SimOne_Data):
	_pack_ = 1
	_fields_ = [
		('UltrasonicRadarsNum', c_int), # Ultrasonic nums
		('detections', SimOne_Data_UltrasonicRadar * SOSM_ULTRASONICRADAR_SIZE_MAX)]# Ultrasonics information


SOSM_SENSOR_DETECTIONS_OBJECT_SIZE_MAX = 256


class SimOne_Obstacle_Type(c_int):
	ESimOne_Obstacle_Type_Unknown = 0
	ESimOne_Obstacle_Type_Pedestrian = 4
	ESimOne_Obstacle_Type_Pole = 5
	ESimOne_Obstacle_Type_Car = 6
	ESimOne_Obstacle_Type_Static = 7
	ESimOne_Obstacle_Type_Bicycle = 8
	ESimOne_Obstacle_Type_Fence = 9
	ESimOne_Obstacle_Type_RoadMark = 12
	ESimOne_Obstacle_Type_TrafficSign = 13
	ESimOne_Obstacle_Type_TrafficLight = 15
	ESimOne_Obstacle_Type_Rider = 17
	ESimOne_Obstacle_Type_Truck = 18
	ESimOne_Obstacle_Type_Bus = 19
	ESimOne_Obstacle_Type_Train = 20
	ESimOne_Obstacle_Type_Motorcycle = 21
	ESimOne_Obstacle_Type_Dynamic = 22
	ESimOne_Obstacle_Type_GuardRail = 23
	ESimOne_Obstacle_Type_SpeedLimitSign = 26
	ESimOne_Obstacle_Type_BicycleStatic = 27
	ESimOne_Obstacle_Type_RoadObstacle = 29

class SimOne_Data_SensorDetections_Entry(Structure):
	_pack_ = 1
	_fields_ = [
	('id', c_int),			# Detection Object ID
	('type', SimOne_Obstacle_Type),		# Detection Object Type
	('posX', c_float),		# Detection Object Position X in meter
	('posY', c_float),		# Detection Object Position Y in meter
	('posZ', c_float),		# Detection Object Position Z in meter
	('oriX', c_float),		# Rotation X in radian
	('oriY', c_float),		# Rotation Y in radian
	('oriZ', c_float),		# Rotation Z in radian
	('length', c_float),	# Detection Object Length in meter
	('width', c_float),		# Detection Object Width in meter
	('height', c_float),	# Detection Object Height in meter
	('range', c_float),		# Detection Object nearest range in meter
	('velX', c_float),		# Detection Object Velocity X
	('velY', c_float),		# Detection Object Velocity Y
	('velZ', c_float),		# Detection Object Velocity Z
	('probability', c_float),	# Detection probability
	('relativePosX', c_float),	# Relative position X in sensor space
	('relativePosY', c_float),	# Relative position Y in sensor space
	('relativePosZ', c_float),	# Relative position Z in sensor space
	('relativeRotX', c_float),	# Relative rotation X in sensor space
	('relativeRotY', c_float),	# Relative rotation Y in sensor space
	('relativeRotZ', c_float),	# Relative rotation Z in sensor space
	('relativeVelX', c_float),	# Relative velocity X in sensor space
	('relativeVelY', c_float),	# Relative velocity Y in sensor space
	('relativeVelZ', c_float),	# Relative velocity Z in sensor space
	('bbox2dMinX', c_float),	# bbox2d minX in pixel if have
	('bbox2dMinY', c_float),	# bbox2d minY in pixel if have
	('bbox2dMaxX', c_float),	# bbox2d maxX in pixel if have
	('bbox2dMaxY', c_float)]	# bbox2d maxY in pixel if have


class SimOne_Data_Environment(Structure):
	_pack_ = 1
	_fields_ = [
	('timeOfDay', c_float),		# Environment timeOfDay
	('heightAngle', c_float),		# Environment heightAngle
	('directionalLight', c_float),		# Environment directionalLight
	('ambientLight', c_float),		# Environment ambientLight
	('artificialLight', c_float),		# Environment artificialLight
	('cloudDensity', c_float),		# Environment cloudDensity
	('fogDensity', c_float),	# Environment fogDensity
	('rainDensity', c_float),		# Environment rainDensity
	('snowDensity', c_float),	# Environment snowDensity
	('groundHumidityLevel', c_float),	# Environment groundHumidityLevel
	('groundDirtyLevel', c_float)]	# Environment groundDirtyLevel


class SimOne_Data_SensorDetections(SimOne_Data):
	_pack_ = 1
	_fields_ = [
	('objectSize', c_int), # Detection Object Size
	('objects', SimOne_Data_SensorDetections_Entry*SOSM_SENSOR_DETECTIONS_OBJECT_SIZE_MAX)] # Detection Objects 


SOSM_OSI_DATA_SIZE_MAX = 1024*1024*8


class SimOne_Data_OSI(SimOne_Data):
	_pack_ = 1
	_fields_ = [
	('dataSize', c_int),
	('data', c_char * SOSM_OSI_DATA_SIZE_MAX)]


SOSM_LANE_NAME_MAX = 128
SOSM_LANE_POINT_MAX = 65535
SOSM_NEAR_LANE_MAX = 128
SOSM_LANE_LINK_MAX = 1024
SOSM_PARKING_SPACE_MAX = 65535
SOSM_PARKING_SPACE_KNOTS_MAX = 4


class SimOneLaneName(Structure):
	_pack_ = 1
	_fields_ = [
	('nameSize', c_int),
	('name', c_char * SOSM_LANE_NAME_MAX)]


class ESimOneLaneType(c_int):
	ESimOneLaneType_none = 0
	ESimOneLaneType_driving = 1
	ESimOneLaneType_stop = 2
	ESimOneLaneType_shoulder = 3
	ESimOneLaneType_biking = 4
	ESimOneLaneType_sidewalk = 5
	ESimOneLaneType_border = 6
	ESimOneLaneType_restricted = 7
	ESimOneLaneType_parking = 8
	ESimOneLaneType_bidirectional = 9
	ESimOneLaneType_median = 10
	ESimOneLaneType_special1 = 11
	ESimOneLaneType_special2 = 12
	ESimOneLaneType_special3 = 13
	ESimOneLaneType_roadWorks = 14
	ESimOneLaneType_tram = 15
	ESimOneLaneType_rail = 16
	ESimOneLaneType_entry = 17
	ESimOneLaneType_exit = 18
	ESimOneLaneType_offRamp = 19
	ESimOneLaneType_onRamp = 20
	ESimOneLaneType_mwyEntry = 21
	ESimOneLaneType_mwyExit = 22

class ESimOneDataBoundaryType(c_int):
	BoundaryType_none = 0
	BoundaryType_solid = 1
	BoundaryType_broken = 2
	BoundaryType_solid_solid = 3
	BoundaryType_solid_broken = 4
	BoundaryType_broken_solid = 5
	BoundaryType_broken_broken = 6
	BoundaryType_botts_dots = 7
	BoundaryType_grass = 8
	BoundaryType_curb = 9

class ESimOneDataBoundaryColor(c_int):
	BoundaryColor_standard = 0
	BoundaryColor_blue = 1
	BoundaryColor_green = 2
	BoundaryColor_red = 3
	BoundaryColor_white = 4
	BoundaryColor_yellow = 5


class SimOneNearLanes(Structure):
	_pack_ = 1
	_fields_ = [
	('laneNameSize', c_int),
	('laneName', SimOneLaneName *SOSM_NEAR_LANE_MAX )]


class SimOnePoint(Structure):
	_pack_ = 1
	_fields_ = [
	('x', c_double),
	('y', c_double),
	('z', c_double)]

class SimOneData_Vec3f(Structure):
	_pack_ = 1
	_fields_ = [
	('x', c_float),
	('y', c_float),
	('z', c_float)]

class ESimOneData_LaneParameter(Structure):
	_pack_ = 1
	_fields_ = [
	('C0', c_float),
	('C1', c_float),
	('C2', c_float),
	('C3', c_float),
	('firstPoints', SimOneData_Vec3f),
	('endPoints', SimOneData_Vec3f),
	('length', c_float)]

SOSM_SENSOR_LANE_OBJECT_SIZE_MAX = 256
SOSM_SENSOR_Boundary_OBJECT_SIZE_MAX = 80
class SimOne_Data_LaneInfo(SimOne_Data):
	_pack_ = 1
	_fields_ = [
		('id', c_int),
		('laneType', ESimOneLaneType),
		('laneLeftID', c_int),
		('laneRightID', c_int),
		('lanePredecessorID', c_int * SOSM_SENSOR_LANE_OBJECT_SIZE_MAX),
		('laneSuccessorID', c_int * SOSM_SENSOR_LANE_OBJECT_SIZE_MAX),
		('leftBoundaryType', ESimOneDataBoundaryType),
	    ('rightBoundaryType', ESimOneDataBoundaryType),
		('leftBoundaryColor', ESimOneDataBoundaryColor),
		('rightBoundaryColor', ESimOneDataBoundaryColor),
		('leftBoundaryWidth', c_float),
		('rightBoundaryWidth', c_float),
		('leftBoundaryPoints', SimOneData_Vec3f * SOSM_SENSOR_Boundary_OBJECT_SIZE_MAX),
		('rightBoundaryPoints', SimOneData_Vec3f * SOSM_SENSOR_Boundary_OBJECT_SIZE_MAX),
		('centerBoundaryPoints', SimOneData_Vec3f * SOSM_SENSOR_Boundary_OBJECT_SIZE_MAX),
		('laneLeftParameter', ESimOneData_LaneParameter),
		('laneRightParameter', ESimOneData_LaneParameter),
		('laneCenterParameter', ESimOneData_LaneParameter)]




class SimOneLaneInfo(Structure):
	_pack_ = 1
	_fields_ = [
	('laneName', SimOneLaneName),
	('leftBoundarySize', c_int),
	('leftBoundary', SimOnePoint *SOSM_LANE_POINT_MAX ),
	('rightBoundarySize', c_int),
	('rightBoundary', SimOnePoint *SOSM_LANE_POINT_MAX ),
	('centerLineSize', c_int),
	('centerLine', SimOnePoint *SOSM_LANE_POINT_MAX )]


class SimOneLaneLink(Structure):
	_pack_ = 1
	_fields_ = [
	('predecessorLaneNameSize', c_int),
	('predecessorLaneName', SimOneLaneName * SOSM_LANE_LINK_MAX),
	('successorLaneNameSize', c_int),
	('successorLaneName', SimOneLaneName * SOSM_LANE_LINK_MAX),
	('leftNeighborLaneName', SimOneLaneName),
	('rightNeighborLaneName', SimOneLaneName)]


class SimOneParkingSpaceIds(Structure):
	_pack_ = 1
	_fields_ = [
	('idSize', c_int),
	('id', SimOneLaneName *SOSM_PARKING_SPACE_MAX )]


class SimOneParkingSpaceKnots(Structure):
	_pack_ = 1
	_fields_ = [
	('knotSize', c_int),
	('knot', SimOnePoint *SOSM_PARKING_SPACE_KNOTS_MAX )]


SOSM_WAYPOINTS_SIZE_MAX = 100


class SimOne_Data_WayPoints_Entry(Structure):
	_pack_ = 1
	_fields_ = [
	('index', c_int),
	('posX', c_float), # MainVehicle WayPoints X on Opendrive (by meter)
	('posY', c_float),  # MainVehicle WayPoints Y on Opendrive (by meter)
	('heading_x', c_float),
	('heading_y', c_float),
	('heading_z', c_float),
	('heading_w', c_float),]


class SimOne_Data_WayPoints(SimOne_Data):
	_pack_ = 1
	_fields_ = [
	('wayPointsSize', c_int),	# MainVehicle WayPoints size
	('wayPoints', SimOne_Data_WayPoints_Entry*SOSM_WAYPOINTS_SIZE_MAX)]  # WayPoints, 300 max


class SimOne_Driver_Status(c_int):
	ESimOne_Driver_Status_Unknown = 0,
	ESimOne_Driver_Status_Running = 1,
	ESimOne_Driver_Status_Finished = 2


class SimOne_Data_Driver_Status(SimOne_Data):
	_pack_ = 1
	_fields_ = [
		('driverStatus', SimOne_Driver_Status)
	]


# 新的接口的回调函数
SimOne_StartCaseFuncType = CFUNCTYPE(c_void_p)
SimOne_StopCaseFuncType = CFUNCTYPE(c_void_p)
SimOne_MainVehicleStatusUpdateFuncType = CFUNCTYPE(c_void_p, POINTER(SimOne_Data_MainVehicle_Status))

SimOne_FrameStartFuncType = CFUNCTYPE(c_void_p, c_int)
SimOne_FrameEndFuncType = CFUNCTYPE(c_void_p, c_int)

SimOne_GpsCbFuncType = CFUNCTYPE(c_void_p, POINTER(SimOne_Data_Gps))
SimOne_ObstacleFuncType = CFUNCTYPE(c_void_p, POINTER(SimOne_Data_Obstacle))
SimOne_TrafficLightFuncType = CFUNCTYPE(c_void_p, POINTER(SimOne_Data_TrafficLights))
SimOne_ScenarioEventCBType = CFUNCTYPE(c_void_p, c_int, c_char_p, c_char_p)
# 新的接口的回调函数到这里截止

GpsCbFuncType = CFUNCTYPE(c_void_p, c_int, POINTER(SimOne_Data_Gps))
GroundTruthCbFuncType = CFUNCTYPE(c_void_p, c_int, POINTER(SimOne_Data_Obstacle))
CameraSensorInfoCbFuncType = CFUNCTYPE(c_void_p,c_int, c_int, POINTER(SimOne_Data_LaneInfo))
UltrasonicsCbFuncType = CFUNCTYPE(c_void_p, c_int, POINTER(SimOne_Data_UltrasonicRadars))
ImageCbFuncType = CFUNCTYPE(c_void_p, c_int, c_int,POINTER(SimOne_Data_Image))
StreamingImageCbFuncType = CFUNCTYPE(c_void_p,POINTER(SimOne_Data_Image))
PointCloudCbFuncType = CFUNCTYPE(c_void_p, c_int, c_int,POINTER(SimOne_Data_Point_Cloud))
StreamingPointCloudCbFuncType = CFUNCTYPE(c_void_p,POINTER(SimOne_Data_Point_Cloud))
RadarDetectionCbFuncType = CFUNCTYPE(c_void_p, c_int, c_int,POINTER(SimOne_Data_RadarDetection))
SensorDetectionsCbFuncType = CFUNCTYPE(c_void_p, c_int, c_int,POINTER(SimOne_Data_SensorDetections))
OSIGroundTruthCbFuncType = CFUNCTYPE(c_void_p, c_int,POINTER(SimOne_Data_OSI))
OSISensorDataCbFuncType = CFUNCTYPE(c_void_p, c_int, c_int,POINTER(SimOne_Data_OSI))

G_API_StartCase_CB = None
G_API_StopCase_CB = None
G_API_MainVehicleStatusCB = None
G_API_FrameStart_CB = None
G_API_FrameStop_CB = None
G_API_Gps_CB = None
G_API_Obstacle_CB = None
G_API_TrafficLight_CB = None
G_API_ScenarioEvent_CB = None


SIMONEAPI_GPS_CB = None
SIMONEAPI_GROUNDTRUTH_CB = None
SIMONEAPI_CAMERASENSORLANEINFO_CB = None
SIMONEAPI_IMAGE_CB = None
SIMONEAPI_StreamingIMAGE_CB = None
SIMONEAPI_POINTCLOUD_CB = None
SIMONEAPI_RADARDETECTION_CB = None
SIMONEAPI_SENSOR_DETECTIONS_CB = None
SIMONEAPI_OSI_GROUNDTRUTH_CB = None
SIMONEAPI_OSI_SENSORDATA_CB = None
SIMONEAPI_ULTRASONICS_CB = None


def _api_startcase_cb():
	global G_API_StartCase_CB
	if G_API_StartCase_CB is None:
		return
	G_API_StartCase_CB()


def _api_stopcase_cb():
	global G_API_StopCase_CB
	if G_API_StopCase_CB is None:
		return
	G_API_StopCase_CB()


def _api_mainvehiclestatusupdate_cb(mainVehicleId, data):
	global G_API_MainVehicleChangeStatusCB
	if G_API_MainVehicleChangeStatusCB is None:
		return
	G_API_MainVehicleChangeStatusCB(mainVehicleId, data)


def _api_framestart_cb(frame):
	global G_API_FrameStart_CB
	if G_API_FrameStart_CB is None:
		return
	G_API_FrameStart_CB(frame)


def _api_framestop_cb(frame):
	global G_API_FrameStop_CB
	if G_API_FrameStop_CB is None:
		return
	G_API_FrameStop_CB(frame)


def _api_gps_cb(data):
	global G_API_Gps_CB
	if G_API_Gps_CB is None:
		return
	G_API_Gps_CB(data)


def _api_obstacle_cb(data):
	global G_API_Obstacle_CB
	if G_API_Obstacle_CB is None:
		return
	G_API_Obstacle_CB(data)


def _api_trafficLight_cb(data):
	global G_API_TrafficLight_CB
	if G_API_TrafficLight_CB is None:
		return
	G_API_TrafficLight_CB(data)
    
def _api_scenarioEvent_cb(mainVehicleId, evt, data):
	global G_API_ScenarioEvent_CB
	if G_API_ScenarioEvent_CB is None:
		return
	G_API_ScenarioEvent_CB(mainVehicleId, evt, data)


def _simoneapi_gps_cb(mainVehicleId, data):
	global SIMONEAPI_GPS_CB
	SIMONEAPI_GPS_CB(mainVehicleId, data)


def _simoneapi_groundtruth_cb(mainVehicleId, data):
	global SIMONEAPI_GROUNDTRUTH_CB
	SIMONEAPI_GROUNDTRUTH_CB(mainVehicleId, data)

def _simoneapi_camerasensorlaneinfo_cb(mainVehicleId, sensorId, data):
	global SIMONEAPI_CAMERASENSORLANEINFO_CB
	SIMONEAPI_CAMERASENSORLANEINFO_CB(mainVehicleId, sensorId, data)

def _simoneapi_ultrasonics_cb(mainVehicleId, data):
	global SIMONEAPI_ULTRASONICS_CB
	SIMONEAPI_ULTRASONICS_CB(mainVehicleId, data)


def _simoneapi_image_cb(mainVehicleId, sensorId, data):
	global SIMONEAPI_IMAGE_CB
	SIMONEAPI_IMAGE_CB(mainVehicleId, sensorId, data)


def _simoneapi_streamingimage_cb(data):
	global SIMONEAPI_StreamingIMAGE_CB
	SIMONEAPI_StreamingIMAGE_CB(data)


def _simoneapi_pointcloud_cb(mainVehicleId, sensorId, data):
	global SIMONEAPI_POINTCLOUD_CB
	SIMONEAPI_POINTCLOUD_CB(mainVehicleId, sensorId, data)


def _simoneapi_streamingpointcloud_cb(data):
	global SIMONEAPI_StreamingPOINTCLOUD_CB
	SIMONEAPI_StreamingPOINTCLOUD_CB( data)


def _simoneapi_radardetection_cb(mainVehicleId, sensorId, data):
	global SIMONEAPI_RADARDETECTION_CB
	SIMONEAPI_RADARDETECTION_CB(mainVehicleId, sensorId, data)


def _simoneapi_sensor_detections_cb(mainVehicleId, sensorId, data):
	global SIMONEAPI_SENSOR_DETECTIONS_CB
	SIMONEAPI_SENSOR_DETECTIONS_CB(mainVehicleId, sensorId, data)


def _simoneapi_osi_groundtruth_cb(mainVehicleId, data):
	global SIMONEAPI_OSI_GROUNDTRUTH_CB
	SIMONEAPI_OSI_GROUNDTRUTH_CB(mainVehicleId, data)


def _simoneapi_osi_sensordata_cb(mainVehicleId,sensorId, data):
	global SIMONEAPI_OSI_SENSORDATA_CB
	SIMONEAPI_OSI_SENSORDATA_CB(mainVehicleId,sensorId, data)


api_startcase_cb = SimOne_StartCaseFuncType(_api_startcase_cb)
api_stopcase_cb = SimOne_StopCaseFuncType(_api_stopcase_cb)
api_mainvehiclestatusupdate_cb = SimOne_MainVehicleStatusUpdateFuncType(_api_mainvehiclestatusupdate_cb)
api_framestart_cb = SimOne_FrameStartFuncType(_api_framestart_cb)
api_framestop_cb = SimOne_FrameEndFuncType(_api_framestop_cb)
api_gps_cb = SimOne_GpsCbFuncType(_api_gps_cb)
api_obstacle_cb = SimOne_ObstacleFuncType(_api_obstacle_cb)
api_trafficLight_cb = SimOne_TrafficLightFuncType(_api_trafficLight_cb)
api_scenarioEvent_cb = SimOne_ScenarioEventCBType(_api_scenarioEvent_cb)

simoneapi_gps_cb_func = GpsCbFuncType(_simoneapi_gps_cb)
simoneapi_groundtruth_cb_func = GroundTruthCbFuncType(_simoneapi_groundtruth_cb)
simoneapi_camerasensorlaneinfo_cb_func = CameraSensorInfoCbFuncType(_simoneapi_camerasensorlaneinfo_cb)
simoneapi_ultrasonics_cb_func = UltrasonicsCbFuncType(_simoneapi_ultrasonics_cb)
simoneapi_image_cb_func = ImageCbFuncType(_simoneapi_image_cb)
simoneapi_streamingimage_cb_func = StreamingImageCbFuncType(_simoneapi_streamingimage_cb)
simoneapi_pointcloud_cb_func = PointCloudCbFuncType(_simoneapi_pointcloud_cb)
simoneapi_streamingpointcloud_cb_func = StreamingPointCloudCbFuncType(_simoneapi_streamingpointcloud_cb)
simoneapi_radardetection_cb_func = RadarDetectionCbFuncType(_simoneapi_radardetection_cb)
simoneapi_sensor_detections_cb_func = SensorDetectionsCbFuncType(_simoneapi_sensor_detections_cb)
simoneapi_osi_groundtruth_cb_func = OSIGroundTruthCbFuncType(_simoneapi_osi_groundtruth_cb)
simoneapi_osi_sensordata_cb_func = OSISensorDataCbFuncType(_simoneapi_osi_sensordata_cb)


# 新的API
# 获取版本号
def SoAPIGetVersion():
	SimoneIOAPI.GetVersion.restype = c_char_p
	return SimoneIOAPI.GetVersion()


def SoAPISetupPerformance(isOpen, intervalPacketCount, filePath):
	SimoneIOAPI.SetupPerformance.restype = c_bool
	return SimoneIOAPI.SetupPerformance(isOpen, intervalPacketCount, filePath)


def SoAPISetupLogLevel(level, flag):
	SimoneIOAPI.SetupLogLevel.restype = c_bool
	return SimoneIOAPI.SetupLogLevel(level, flag)


def SoAPISetServerInfo(server='127.0.0.1', port=23789):
	_input = create_string_buffer(server.encode(), 256)
	SimoneIOAPI.SetServerInfo.restype = c_bool
	return SimoneIOAPI.SetServerInfo(_input, port)


# new
def SoAPIStartSimOneNode(startcase, stopcase):
	SimoneIOAPI.StartSimOneNode.restype = c_bool
	global G_API_StartCase_CB
	global G_API_StopCase_CB
	if startcase == 0:
		startcase = None
	if stopcase == 0:
		stopcase = None
	G_API_StartCase_CB = startcase
	G_API_StopCase_CB = stopcase
	ret = SimoneIOAPI.StartSimOneNode(api_startcase_cb, api_stopcase_cb)
	return ret


def SoAPIStopSimOneNode():
	SimoneIOAPI.StopSimOneNode.restype = c_bool
	ret = SimoneIOAPI.StopSimOneNode()
	return ret


def SoAPISimOneNodeReady():
	SimoneIOAPI.SimOneNodeReady.restype = c_bool
	ret = SimoneIOAPI.SimOneNodeReady()
	return ret


def SoAPIGetCaseInfo(data):
	SimoneIOAPI.GetCaseInfo.restype = c_bool
	return SimoneIOAPI.GetCaseInfo(pointer(data))


def SoAPIGetCaseRunStatus():
	SimoneIOAPI.GetCaseRunStatus.restype = c_int
	return SimoneIOAPI.GetCaseRunStatus()


def SoAPIGetMainVehicleList(data):
	SimoneIOAPI.GetMainVehicleList.restype = c_bool
	return SimoneIOAPI.GetMainVehicleList(pointer(data), True)


# new
def SoAPISubMainVehicle(mainVehicleId, isJoinTimeLoop):
	SimoneIOAPI.SubMainVehicle.restype = c_bool
	ret = SimoneIOAPI.SubMainVehicle(mainVehicleId, isJoinTimeLoop)
	return ret


# new
def SoAPIGetMainVehicleStatus(data):
	SimoneIOAPI.GetMainVehicleStatus.restype = c_bool
	return SimoneIOAPI.GetMainVehicleStatus(pointer(data))


# new
def SoAPISetMainVehicleStatusCB(cb):
	SimoneIOAPI.SetMainVehicleStatusCB.restype = c_bool
	global G_API_MainVehicleStatusCB
	if cb == 0:
		cb = None

	G_API_MainVehicleStatusCB = cb
	return SimoneIOAPI.SetMainVehicleStatusCB(api_mainvehiclestatusupdate_cb)


def SoAPIWait():
	SimoneIOAPI.Wait.restype = c_int
	return SimoneIOAPI.Wait()


def SoAPINextFrame(frame):
	SimoneIOAPI.NextFrame.restype = c_void_p
	return SimoneIOAPI.NextFrame(frame)


def SoAPIGetSimOneGps(data):
	SimoneIOAPI.GetSimOneGps.restype = c_bool
	return SimoneIOAPI.GetSimOneGps(pointer(data))

def SoAPIRegisterSimOneVehicleState(data):
    SimoneIOAPI.RegisterSimOneVehicleState.restype = c_bool
    return SimoneIOAPI.RegisterSimOneVehicleState(pointer(data), len(data))

def SoAPIGetSimOneVehicleState(data):
	SimoneIOAPI.GetSimOneVehicleState.restype = c_bool
	return SimoneIOAPI.GetSimOneVehicleState(pointer(data))

def SoAPIGetSimOneGroundTruth(data):
	SimoneIOAPI.GetSimOneGroundTruth.restype = c_bool
	return SimoneIOAPI.GetSimOneGroundTruth(pointer(data))


def SoAPISetFrameCB(startcb, stopcb):
	SimoneIOAPI.SetFrameCB.restype = c_bool
	global G_API_FrameStart_CB
	global G_API_FrameStop_CB
	if startcb == 0:
		startcb = None
	if stopcb == 0:
		stopcb = None

	G_API_FrameStart_CB = startcb
	G_API_FrameStop_CB = stopcb

	ret = SimoneIOAPI.SetFrameCB(api_framestart_cb, api_framestop_cb)
	return ret


def SoAPISetSimOneGpsCB(cb):
	if cb == 0:
		cb = None
	global G_API_Gps_CB

	G_API_Gps_CB = cb
	SimoneIOAPI.SetSimOneGpsCB.restype = c_bool
	ret = SimoneIOAPI.SetSimOneGpsCB(api_gps_cb)

	return ret

# new
def SoAPISetSimOneGroundTruthCB(cb):
	if cb == 0:
		cb = None
	global G_API_Obstacle_CB
	G_API_Obstacle_CB = cb
	SimoneIOAPI.SetSimOneGroundTruthCB.restype = c_bool
	ret = SimoneIOAPI.SetSimOneGroundTruthCB(api_obstacle_cb)

	return ret


def SoAPISetSensorPhysicalbasedDataEnable(enable):
	SimoneIOAPI.SetSensorPhysicalbasedDataEnable.restype = c_void_p
	return SimoneIOAPI.SetSensorPhysicalbasedDataEnable(enable)


def SoAPISetSensorObjectbasedDataEnable(enable):
	SimoneIOAPI.SetSensorObjectbasedDataEnable.restype = c_void_p
	return SimoneIOAPI.SetSensorObjectbasedDataEnable(enable)


def SoAPISetSensorOSIDataEnable(enable):
	SimoneIOAPI.SetSensorOSIDataEnable.restype = c_void_p
	return SimoneIOAPI.SetSensorOSIDataEnable(enable)
    
# new
def SoAPISetScenarioEventCB(cb):
	if cb == 0:
		cb = None
	global G_API_ScenarioEvent_CB
	G_API_ScenarioEvent_CB = cb
	SimoneIOAPI.SetScenarioEventCB.restype = c_bool
	ret = SimoneIOAPI.SetScenarioEventCB(api_scenarioEvent_cb)

	return ret
    
# 新的API到截止到这里


def SoApiStart():
	SimoneIOAPI.Start.restype = c_bool
	return SimoneIOAPI.Start()


def SoOSIStart():
	SimoneIOAPI.OSIStart.restype = c_bool
	return SimoneIOAPI.OSIStart()


def SoApiStop():
	SimoneIOAPI.Stop.restype = c_bool
	return SimoneIOAPI.Stop()


def SoApiSetPose(mainVehicleId, poseControl):
	return SimoneIOAPI.SetPose(mainVehicleId, pointer(poseControl))


def SoApiSetDrive(mainVehicleId, driveControl):
	return SimoneIOAPI.SetDrive(mainVehicleId, pointer(driveControl))

def SetDriverName(mainVehicleId, driveName):
	return SimoneIOAPI.SetDrive(mainVehicleId, pointer(driveName))

def SoApiSetVehicleEvent(mainVehicleId, vehicleEventInfo):
	return SimoneIOAPI.SetVehicleEvent(mainVehicleId, pointer(vehicleEventInfo))


def SoGetGps(mainVehicleId, gpsData):
	return SimoneIOAPI.GetGps(mainVehicleId, pointer(gpsData))


def SoApiSetGpsUpdateCB(cb):
	global SIMONEAPI_GPS_CB
	SimoneIOAPI.SetGpsUpdateCB(simoneapi_gps_cb_func)
	SIMONEAPI_GPS_CB = cb


def SoGetGroundTruth(mainVehicleId, obstacleData):
	return SimoneIOAPI.GetGroundTruth(mainVehicleId, pointer(obstacleData))


def SoGetTrafficLights(mainVehicleId, opendriveLightId, trafficLight):
	return SimoneIOAPI.GetTrafficLight(mainVehicleId, opendriveLightId, pointer(trafficLight))


def SoGetSensorConfigurations(sensorConfigurations):
	return SimoneIOAPI.GetSensorConfigurations(pointer(sensorConfigurations))


def SoGetUltrasonicRadar(mainVehicleId, sensorId, ultrasonics):
	return SimoneIOAPI.GetUltrasonicRadar(mainVehicleId, sensorId, pointer(ultrasonics))

def SoGetCameraSensorLaneInfo(mainVehicleId, sensorId,pLaneInfo):
	return SimoneIOAPI.GetCameraSensorLaneInfo(mainVehicleId, sensorId, pointer(pLaneInfo))

def SoGetUltrasonicRadars(mainVehicleId, ultrasonics):
	return SimoneIOAPI.GetUltrasonicRadars(mainVehicleId, pointer(ultrasonics))


def SoApiSetGroundTruthUpdateCB(cb):
	global SIMONEAPI_GROUNDTRUTH_CB
	SimoneIOAPI.SetGroundTruthUpdateCB(simoneapi_groundtruth_cb_func)
	SIMONEAPI_GROUNDTRUTH_CB = cb

def SoApiSetCameraSensorLaneInfoCB(cb):
	global SIMONEAPI_CAMERASENSORLANEINFO_CB
	SimoneIOAPI.SetCameraSensorLaneInfoCB(simoneapi_camerasensorlaneinfo_cb_func)
	SIMONEAPI_CAMERASENSORLANEINFO_CB = cb

def SoApiSetUltrasonicRadarsCB(cb):
	global SIMONEAPI_ULTRASONICS_CB
	SimoneIOAPI.SetUltrasonicRadarsCB(simoneapi_ultrasonics_cb_func)
	SIMONEAPI_ULTRASONICS_CB = cb


def SoGetImage(mainVehicleId, sensorId, imageData):
	SimoneIOAPI.GetImage.restype = c_bool
	return SimoneIOAPI.GetImage(mainVehicleId, sensorId, pointer(imageData))


def SoGetStreamingImage(ip, port, imageData):
	_input = create_string_buffer(ip.encode(), 256)
	SimoneStreamingIOAPI.GetStreamingImage.restype = c_bool
	return SimoneStreamingIOAPI.GetStreamingImage(_input, port, pointer(imageData))


def SoApiSetImageUpdateCB(cb):
	global SIMONEAPI_IMAGE_CB
	SimoneIOAPI.SetImageUpdateCB(simoneapi_image_cb_func)
	SIMONEAPI_IMAGE_CB = cb


def SoApiSetStreamingImageCB(ip, port, cb):
	global SIMONEAPI_StreamingIMAGE_CB
	_input = create_string_buffer(ip.encode(), 256)
	SimoneStreamingIOAPI.SetStreamingImageCB(_input, port, simoneapi_streamingimage_cb_func)
	SIMONEAPI_StreamingIMAGE_CB = cb


def SoGetPointCloud(mainVehicleId, sensorId, pointCloudData):
	return SimoneIOAPI.GetPointCloud(mainVehicleId, sensorId, pointer(pointCloudData))


def SoGetStreamingPointCloud(ip, port,infoPort, pointCloudData):
	_input = create_string_buffer(ip.encode(), 256)
	SimoneStreamingIOAPI.GetStreamingPointCloud.restype = c_bool
	return SimoneStreamingIOAPI.GetStreamingPointCloud(_input, port, infoPort,pointer(pointCloudData))


def SoApiSetPointCloudUpdateCB(cb):
	global SIMONEAPI_POINTCLOUD_CB
	SimoneIOAPI.SetPointCloudUpdateCB(simoneapi_pointcloud_cb_func)
	SIMONEAPI_POINTCLOUD_CB = cb


def SoApiSetStreamingPointCloudUpdateCB(ip, port,infoPort, cb):
	global SIMONEAPI_StreamingPOINTCLOUD_CB
	_input = create_string_buffer(ip.encode(), 256)
	SimoneStreamingIOAPI.SetStreamingPointCloudUpdateCB(_input, port,infoPort, simoneapi_streamingpointcloud_cb_func)
	SIMONEAPI_StreamingPOINTCLOUD_CB = cb


def SoGetRadarDetections(mainVehicleId, sensorId, detectionData):
	return SimoneIOAPI.GetRadarDetections(mainVehicleId, sensorId, pointer(detectionData))


def SoApiSetRadarDetectionsUpdateCB(cb):
	global SIMONEAPI_RADARDETECTION_CB
	SimoneIOAPI.SetRadarDetectionsUpdateCB(simoneapi_radardetection_cb_func)
	SIMONEAPI_RADARDETECTION_CB = cb


def SoOSIGetSensorData(mainVehicleId,sensorId, pSensorData):
	return SimoneIOAPI.OSIGetSensorData(mainVehicleId, sensorId, pointer(pSensorData))


def SoGetSensorDetections(mainVehicleId, sensorId, sensorDetections):
	return SimoneIOAPI.GetSensorDetections(mainVehicleId, sensorId, pointer(sensorDetections))


def SoGetEnvironment(pEnvironment):
	return SimoneIOAPI.GetEnvironment(pointer(pEnvironment))


def SoSetEnvironment(pEnvironment):
	return SimoneIOAPI.SetEnvironment(pointer(pEnvironment))


def SoSetSignalLights(mainVehicleId, pSignalLight):
	return SimoneIOAPI.SetSignalLights(mainVehicleId, pointer(pSignalLight))


def SoApiSetSensorDetectionsUpdateCB(cb):
	global SIMONEAPI_SENSOR_DETECTIONS_CB
	SimoneIOAPI.SetSensorDetectionsUpdateCB(simoneapi_sensor_detections_cb_func)
	SIMONEAPI_SENSOR_DETECTIONS_CB = cb


def SoOSIGetGroundTruth(mainVehicleId, groundtruthData):
	return SimoneIOAPI.OSIGetGroundTruth(mainVehicleId, pointer(groundtruthData))


def SoApiOSISetGroundTruthUpdateCB(cb):
	global SIMONEAPI_OSI_GROUNDTRUTH_CB
	SimoneIOAPI.OSISetGroundTruthUpdateCB(simoneapi_osi_groundtruth_cb_func)
	SIMONEAPI_OSI_GROUNDTRUTH_CB = cb


def SoApiOSISetSensorDataUpdateCB(cb):
	global SIMONEAPI_OSI_SENSORDATA_CB
	SimoneIOAPI.OSISetSensorDataUpdateCB(simoneapi_osi_sensordata_cb_func)
	SIMONEAPI_OSI_SENSORDATA_CB = cb


def SoGetDriverStatus(mainVehicleId, driverStatusData):
	return SimoneIOAPI.GetDriverStatus(mainVehicleId, pointer(driverStatusData))


def SoGetWayPoints(wayPointsData):
	return SimoneIOAPI.GetWayPoints(pointer(wayPointsData))

def SoBridgeLogOutput(logLevel,*args):
	print(logLevel)
	list = ""
	for arg in args:
		list+=arg
	logStr = bytes(list,encoding='utf-8')
	return SimoneIOAPI.bridgeLogOutput(logLevel,logStr)
