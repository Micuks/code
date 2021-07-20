
#include "DataElement.hpp"
#include "SSD/SimVector.h"

/** 1 DF_AccelerationSet4Way */
typedef struct AccelerationSet4Way
{
	Acceleration_t lon; //forward positive value
	Acceleration_t lat; //right positive value
	VerticalAcceleration_t vert; //vetical 
	YawRate_t yaw; //The yaw rate is positive clockwise
}f_AccelerationSet4Way;


/** 2 DF_BrakeSysytemStatus */
typedef struct BrakeSystemStatus
{
	e_BrakePedalStatus brakePadel; //brake padel status
	e_BrakeAppliedStatus wheelBrakes;  //wheel brake status
	e_TractionControlStatus traction; //traction status
	e_AntiLockBrakeStatus abs;  //abs statsu
	e_StabilityControlStatus scs; //statbility control status
	e_BrakeBoostApplied brakeBoost; //brake boost status
	e_AuxiliaryBrakeStatus auxBrakes; //auxiliary brake status

}f_BrakeSystemStatus;



/** 21 DF_NodeReferenceID */
typedef struct NodeReferenceID
{
	RoadRegulatorID_t region;
	NodeID_t id;
}f_NodeReferenceID;



/** 3 DF_ConnectingLane */
typedef struct ConnectingLane {
	LaneID_t lane;
	e_AllowedManeuvers mannuver; //AllowedManeuvers
}f_ConnectingLane;



/** 4 DF_Connection */
typedef struct Connection
{
	f_NodeReferenceID remoteIntersection; //global ID
	f_ConnectingLane connectingLane;
	PhaseID_t phaseId;
}f_Connection;


/** 5 DF_ConnectsToList */
typedef SSD::SimVector<f_Connection> ConnectsToList;


/** 6 DF_DDateTime */
typedef struct DDateTime
{
	DYear_t year;
	DMonth_t month;
	DDay_t day;
	DHour_t hour;
	DMinute_t minute;
	DSecond_t second;
	DTimeOffset_t offset;
}f_DDateTime;


/** 41 DF_Position3D */
typedef struct Position3D
{
	Longitude_t lon;
	Latitude_t lat;
	Elevation_t elevation;
}f_Position3D;




/** 42 DF_PositionConfidenceSet */
typedef struct PositionConfidenceSet
{
	e_PositionConfidence pos;
	e_ElevationConfidence elevation;
}f_PositionConfidenceSet;


/** 16 DF_MotionConfidenceSet */
typedef struct MontionConfidenceSet
{
	e_SpeedConfidence speedCfd;
	e_HeadingConfidence headingCfd;
	e_SteeringWheelAngleConfidence steerCfd;
}f_MontionConfidenceSet;


/** 7 DF_FullPositionVector */
typedef struct FullPositionVector
{
	f_DDateTime utcTime;
	f_Position3D pos;
	Heading_t heading;
	e_TransmissionState transmission;
	DE_Speed_t speed;
	f_PositionConfidenceSet posAccuracy;
	e_TimeConfidence timeConfidence;
	f_PositionConfidenceSet posConfidence;
	f_MontionConfidenceSet motionCfd;

}f_FullPositionVector;


/** 49 DF_TimeChangeDetails */
typedef struct TimeChangeDetails
{
	TimeMark_t startTime;
	TimeMark_t minEndTime;
	TimeMark_t maxEndTime;
	TimeMark_t likelyEndTime;
	Confidence_t timeConfidence;
	TimeMark_t nextStartTime;
	TimeMark_t nextDuration;
}f_TimeChangeDetails;


/** 31 DF_PhaseState */
typedef struct PhaseState
{
	e_LightState light;
	f_TimeChangeDetails timing;
}f_PhaseState;


/** 32 DF_PhaseStateList */
typedef SSD::SimVector<f_PhaseState> PhaseStateList_t;

/** 29 DF_Phase */
typedef struct Phase
{
	PhaseID_t id;
	PhaseStateList_t PhaseStates;
}f_Phase;


/** 30 DF_PhaseList */
typedef  SSD::SimVector<f_Phase> PhaseList_t;


/** 8 DF_IntersectionState */
typedef struct IntersectionState
{
	f_NodeReferenceID intersectionId;
	e_IntersectionStatusObject status;
	MinuteOfTheYear_t moy;
	DSecond_t timeStamp;
	PhaseList_t phases;
}f_IntersectionState;

/** 9 DF_IntersectionStateList */
typedef SSD::SimVector<f_IntersectionState> IntersectionStateList_t;


/** 13 DF_LaneTypeAttributes */
typedef struct LaneTypeAttributes
{
	e_LaneAttributes_Vehicle vehicle;
	e_LaneAttributes_CrossWalk crosswalk;
	e_LaneAttributes_Bike bikeLane;
	e_LaneAttributes_Sidewalk sideWalk;
	e_LaneAttributes_Barrier median;
	e_LaneAttributes_Striping striping;
	e_LaneAttributes_TrackedVehicle trackedVehicle;
	e_LaneAttributes_Parking parking;
}f_LaneTypeAttributes;


/** 11 DF_LaneAttributes */
typedef struct LaneAttributes
{
	e_LaneSharing shareWith;
	f_LaneTypeAttributes laneType;
}f_LaneAttributes;



/** 34 DF_Position-LL-24B */
typedef struct Position_LL_XB
{
	OffsetLL_B12_t lon;
	OffsetLL_B12_t lat;
}f_Position_LL_XB;

/** 43 DF_PositionOffsetLL */
typedef struct PositionOffsetLL
{
	f_Position_LL_XB position_LL1;
}f_PositionOffsetLL;



/** 53 DF_VerticalOffset */
typedef union VerticalOffset
{
	VertOffset_BX_t offset;
}f_VerticalOffset;



/** 44 DF_PositionOffsetLLV */
typedef struct PositionOffsetLLV
{
	f_PositionOffsetLL offsetLL;
	f_VerticalOffset offsetV;
}f_PositionOffsetLLV;

/** 46 DF_RoadPoint */
typedef struct RoadPoint {
	f_PositionOffsetLLV posOffset;
}f_RoadPoint;

//LocalENU
typedef struct RoadPoint_base
{
	float x;
	float y;
	float z;
}f_RoadPoint_base;

/** 33 DF_PointList */
typedef SSD::SimVector<f_RoadPoint>  PointList_t;

/** 45 DF_RegulatorySpeedLimit */
typedef struct RegulatorySpeedLimit
{
	e_SpeedLimitType type;
	DE_Speed_t  speed;
}f_RegulatorySpeedLimit;


/** 48 DF_SpeedLimitList */
typedef SSD::SimVector<f_RegulatorySpeedLimit> SpeedLimitList_t;

/** 10 DF_Lane */
typedef struct Lane
{
	LaneID_t laneId;
	f_LaneAttributes laneAttributes;
	e_AllowedManeuvers mannuvers;
	ConnectsToList connectsTo;
	SpeedLimitList_t speedLimits;
	PointList_t points;
}f_Lane;



/** 12 DF_LaneList */
typedef SSD::SimVector<f_Lane> LaneList_t;


/** 17 DF_Movement */
typedef struct Movement
{
	f_NodeReferenceID remoteIntersection;
	PhaseID_t phaseId;
}f_Movement;

/** 18 DF_MovementList */
typedef SSD::SimVector<f_Movement> MovementList_t;


/** 14 DF_Link */
typedef struct Link
{
	DescriptiveName_t name;
	f_NodeReferenceID upstreamNodeId;
	SpeedLimitList_t speedLimits;
	LaneWidth_t lanewidth;
	PointList_t points;
	MovementList_t movements;
	LaneList_t lanes;
}f_Link;

/** 15 DF_LinkList */
typedef SSD::SimVector <f_Link> LinkList_t;


/** 19  DF_Node */
typedef struct Node
{
	DescriptiveName_t name;
	f_NodeReferenceID id;
	f_Position3D refPos;
	LinkList_t inLinks;
}f_Node;

/** 20 DF_NodeList */
typedef SSD::SimVector<f_Node> NodeList_t;

/** 52 DF_VehicleSize */
typedef struct VehicleSize
{
	VehicleWidth_t width;
	VehicleLength_t length;
	VehicleHeight_t height;
}f_VehicleSize;

/** 50 DF_VehicleClassification */
typedef struct VehicleClassification
{
	BasicVehicleClass_t classification;
}f_VehicleClassification;


/** 22 DF_ParticipantData */
typedef struct ParticipantData
{
	e_ParticipantType ptcType;
	int ptcId;
	e_SourceType source;
	int id;
	int plateNo;
	DSecond_t secMark;
	f_PositionOffsetLLV pos;
	f_PositionConfidenceSet accuracy;
	e_TransmissionState transmission;
	DE_Speed_t speed;
	Heading_t heading;
	DE_SteeringWheelAngle_t angle;
	f_MontionConfidenceSet motionCfd;
	f_AccelerationSet4Way accelSet;
	f_VehicleSize size;
	f_VehicleClassification vehicleClass;
}f_ParticipantData;


/** 23 DF_ParticipantList */
typedef SSD::SimVector<f_ParticipantData> ParticipantList_t;

/** 25 DF_PathHistoryPoint */
typedef struct PathHistoryPoint
{
	f_PositionOffsetLLV llvOffset;
	DTimeOffset_t timeOffset;
	DE_Speed_t speed;
	f_PositionConfidenceSet psoAccuracy;
	CoarseHeading_t heading;
}f_PathHistoryPoint;

/** 26 DF_PathHistoryPointList */
typedef SSD::SimVector<f_PathHistoryPoint> PathHistoryPointList_t;


/** 24 DF_PathHistory */
typedef struct PathHistory
{
	f_FullPositionVector initialPosition;
	e_GNSSstatus currGNSSstatus;
	PathHistoryPointList_t crumbData;
}f_PathHistory;

/** 27 DF_PathPointList */
typedef SSD::SimVector<f_PositionOffsetLLV> PathPointList_t;

/** 28 DF_PathPrediction */
typedef struct PathPrediction
{
	RadiusOfCurvature_t radiusOfCurve;
	Confidence_t confidence;
}f_PathPrediction;


/** 47 DF_SignalState */
typedef struct SignalState
{
	e_IntersectionStatusObject status;
	MinuteOfTheYear_t moy;
	DSecond_t timeStamp;
	PhaseList_t phases;
}f_SignalState;


typedef struct TrafficLight
{
	int state;
	int remainTime;
}f_TrafficLight;

/** 51 DF_VehicleSafetyExtension */
typedef struct VehicleSafetyExtension
{
	int events;
	f_PathHistory pathHistory;
	f_PathPrediction pathPrediction;
	e_ExteriorLights lights;
	SSD::SimVector<f_TrafficLight> trafficLights;
}f_VehicleSafetyExtension;
