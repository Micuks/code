
#ifndef DataElement_H_
#define DataElement_H_

#include <string>
using namespace std;

/**1 DE_Acceleration */
typedef float Acceleration_t;

/**2 DE_AlertType */
typedef int AlertType_t;

/**3 DE_AllowedManeuvers*/
typedef enum AllowedManeuvers {
	AllowedManeuvers_maneuverStraightAllowed = 1 << 0,
	AllowedManeuvers_maneuverLeftAllowed = 1 << 1,
	AllowedManeuvers_maneuverRightAllowed = 1 << 2,
	AllowedManeuvers_maneuverUTurnAllowed = 1 << 3, 
	AllowedManeuvers_maneuverLeftTurnOnRedAllowed = 1 << 4,
	AllowedManeuvers_maneuverRightTurnOnRedAllowed = 1 << 5,
	AllowedManeuvers_maneuverLaneChangeAllowed = 1 << 6,
	AllowedManeuvers_maneuverNoStoppingAllowed = 1 << 7,
	AllowedManeuvers_yieldAllwaysRequired = 1 << 8,
	AllowedManeuvers_goWithHalt = 1 << 9,
	AllowedManeuvers_caution = 1 << 10,
	AllowedManeuvers_reserved1 = 1 << 11
} e_AllowedManeuvers;

/**4  DE_AntiLockBrakeStatus*/
typedef enum AntiLockBrakeStatus {
	AntiLockBrakeStatus_unavailable = 0,
	AntiLockBrakeStatus_off = 1,
	AntiLockBrakeStatus_on = 2,
	AntiLockBrakeStatus_engaged = 3
} e_AntiLockBrakeStatus;


/**5 DE_AuxiliaryBrakeStatus */
typedef enum AuxiliaryBrakeStatus {
	AuxiliaryBrakeStatus_unavailable = 0,
	AuxiliaryBrakeStatus_off = 1,
	AuxiliaryBrakeStatus_on = 2,
	AuxiliaryBrakeStatus_reserved = 3
} e_AuxiliaryBrakeStatus;

/**6 DE_BaseVehicleClass */
typedef int BasicVehicleClass_t;


/**7 DE_BrakeAppliedStatus */
typedef enum BrakeAppliedStatus {
	BrakeAppliedStatus_unavailable = 1<<0,
	BrakeAppliedStatus_leftFront = 1<<1,
	BrakeAppliedStatus_leftRear = 1<<2,
	BrakeAppliedStatus_rightFront = 1<<3,
	BrakeAppliedStatus_rightRear = 1<<4
} e_BrakeAppliedStatus;

/** 8 DE_BrakeBoostApplied */
typedef enum BrakeBoostApplied {
	BrakeBoostApplied_unavailable = 0,
	BrakeBoostApplied_off = 1,
	BrakeBoostApplied_on = 2
} e_BrakeBoostApplied;


/** 9 DE_BrakePedalStatus */
typedef enum BrakePedalStatus {
	BrakePedalStatus_unavailable = 0,
	BrakePedalStatus_off = 1,
	BrakePedalStatus_on = 2
} e_BrakePedalStatus;

/**10 DE_CoarseHeading */
typedef float CoarseHeading_t;

/** 11 DE_Confidence */
typedef short Confidence_t;

/** 12 DE_DDay  */

typedef short DDay_t;

/** 13 DE_DescriptiveName */
typedef string DescriptiveName_t;

/** 14 DE_DHour */
typedef short DHour_t;

/** 15 DE_Dminute */
typedef short DMinute_t;

/** 16 DE_DMonth */

typedef short DMonth_t;

/** 17 DE_DSecond */
typedef int DSecond_t;

/** 18 DE_DTimeOffset */
typedef int DTimeOffset_t;

/** 19 DE_DYear */
typedef int DYear_t;

/** 20 DE_Elevation */
typedef float Elevation_t;

/** 21 DE_ElevationConfidence */
typedef enum ElevationConfidence {
	unavailable = 0,
	elev_500_00 = 1,
	elev_200_00 = 2,
	elev_100_00 = 3,
	elev_050_00 = 4,
	elev_020_00 = 5,
	elev_010_00 = 6,
	elev_005_00 = 7,
	elev_002_00 = 8,
	elev_001_00 = 9,
	elev_000_50 = 10,
	elev_000_20 = 11,
	elev_000_10 = 12,
	elev_000_05 = 13,
	elev_000_02 = 14,
	elev_000_01 = 15
}e_ElevationConfidence;

/** 22 DE_ExteriorLights */
typedef enum ExteriorLights {
	ExteriorLights_unavailable = 1 << 0, //
	ExteriorLights_lowBeamHeadlightsOn = 1<<1,  //
	ExteriorLights_highBeamHeadlightsOn = 1<<2, 
	ExteriorLights_leftTurnSignalOn = 1 << 3, //
	ExteriorLights_rightTurnSignalOn = 1 << 4, //
	ExteriorLights_hazardSignalOn = 1 << 5, //
	ExteriorLights_automaticLightControlOn = 1 << 6, //
	ExteriorLights_daytimeRunningLightsOn = 1 << 7, //
	ExteriorLights_fogLightOn = 1 << 8, //
	ExteriorLights_parkingLightsOn = 1 << 9 //
} e_ExteriorLights;

/** 23 DE_GNSSstatus */
typedef enum GNSSstatus {
	GNSSstatus_unavailable = 1 << 0,
	GNSSstatus_isHealthy = 1 << 1,
	GNSSstatus_isMonitored = 1 << 2,
	GNSSstatus_baseStationType = 1 << 3,
	GNSSstatus_aPDOPofUnder5 = 1 << 4,
	GNSSstatus_inViewOfUnder5 = 1 << 5,
	GNSSstatus_localCorrectionsPresent = 1 << 6,
	GNSSstatus_networkCorrectionsPresent = 1 << 7
} e_GNSSstatus;

/** 24 DE_Heading */
typedef float Heading_t;

/** 25 DE_HeadingConfidence */
typedef enum HeadingConfidence {
	HeadingConfidence_unavailable = 0,
	HeadingConfidence_prec10deg = 1,
	HeadingConfidence_prec05deg = 2,
	HeadingConfidence_prec01deg = 3,
	HeadingConfidence_prec0_1deg = 4,
	HeadingConfidence_prec0_05deg = 5,
	HeadingConfidence_prec0_01deg = 6,
	HeadingConfidence_prec0_0125deg = 7
} e_HeadingConfidence;

/** 26 DE_IntersectionStatusObject */
typedef enum IntersectionStatusObject {
	IntersectionStatusObject_manualControlIsEnabled = 1 << 0,
	IntersectionStatusObject_stopTimeIsActivated = 1 << 1,
	IntersectionStatusObject_failureFlash = 1 << 2,
	IntersectionStatusObject_preemptIsActive = 1 << 3,
	IntersectionStatusObject_signalPriorityIsActive = 1 << 4,
	IntersectionStatusObject_fixedTimeOperation = 5,
	IntersectionStatusObject_trafficDependentOperation = 1 << 6,
	IntersectionStatusObject_standbyOperation = 1 << 7,
	IntersectionStatusObject_failureMode = 1 << 8,
	IntersectionStatusObject_off = 1 << 9,
	IntersectionStatusObject_recentMAPmessageUpdate = 1 << 10,
	IntersectionStatusObject_recentChangeInMAPassignedLanesIDsUsed = 1 << 11,
	IntersectionStatusObject_noValidMAPisAvailableAtThisTime = 1 << 12,
	IntersectionStatusObject_noValidSPATisAvailableAtThisTime = 1 << 13
} e_IntersectionStatusObject;

/** 27 DE_LaneAttributes-Barrier */
typedef enum LaneAttributes_Barrier {
	LaneAttributes_Barrier_median_RevocableLane = 1 << 0,
	LaneAttributes_Barrier_median = 1 << 1,
	LaneAttributes_Barrier_whiteLineHashing = 1 << 2,
	LaneAttributes_Barrier_stripedLines = 1 << 3,
	LaneAttributes_Barrier_doubleStripedLines = 1 << 4,
	LaneAttributes_Barrier_trafficCones = 1 << 5,
	LaneAttributes_Barrier_constructionBarrier = 1 << 6,
	LaneAttributes_Barrier_trafficChannels = 1 << 7,
	LaneAttributes_Barrier_lowCurbs = 1 << 8,
	LaneAttributes_Barrier_highCrubs = 1 << 9
} e_LaneAttributes_Barrier;


/** 28 DE_LaneAttributes-Bike */
typedef enum LaneAttributes_Bike{
	LaneAttributes_Bike_bikeRevocableLane = 1 << 0,
	LaneAttributes_Bike_pedestrianUseAllowd = 1 << 1,
	LaneAttributes_Bike_isBikeFlyOverLane = 1 << 2,
	LaneAttributes_Bike_fixedCycleTIme = 1 << 3,
	LaneAttributes_Bike_biDirectionalCycleTime = 1 << 4,
	LaneAttributes_Bike_isolatedByBarrier = 1 << 5,
	LaneAttributes_Bike_unsignalizedSegmentsPresent = 1 << 6
} e_LaneAttributes_Bike;


/** 29 DE_LaneAtttributes-Crosswalk*/
typedef enum LaneAttributes_CrossWalk {
	LaneAttributes_CrossWalk_crosswalkRevocableLane = 1 << 0,
	LaneAttributes_CrossWalk_bicyleUseAllowed = 1 << 1,
	LaneAttributes_CrossWalk_isXwalkFlyOverLane = 1 << 2,
	LaneAttributes_CrossWalk_fixedCycleTime = 1 << 3,
	LaneAttributes_CrossWalk_biDirectionalCycleTimes = 1 << 4,
	LaneAttributes_CrossWalk_hasPushToWalkButton = 1 << 5,
	LaneAttributes_CrossWalk_audioSupport = 1 << 6,
	LaneAttributes_CrossWalk_rfSignalRequestPresent = 1 << 7,
	LaneAttributes_CrossWalk_unsignlizedSegmentsPresent = 1 << 8
} e_LaneAttributes_CrossWalk;


/** 30 DE_LaneAttributes-Parking*/
typedef enum LaneAttributes_Parking {
	LaneAttributes_Parking_parkingRevocableLane = 1 << 0,
	LaneAttributes_Parking_parallelParkingInUse = 1 << 1,
	LaneAttributes_Parking_headInParkingInUse = 1 << 2,
	LaneAttributes_Parking_doNotParkZone = 1 << 3,
	LaneAttributes_Parking_parkingForBusUse = 1 << 4,
	LaneAttributes_Parking_parkingForTaxiUse = 1 << 5,
	LaneAttributes_Parking_noPublicParkingUse = 1 << 6
} e_LaneAttributes_Parking;

/** 31 DE_LaneAttributes-Sidewalk*/
typedef enum LaneAttributes_Sidewalk {
	LaneAttributes_Sidewalk_sidewalk_RevocableLane = 1 << 0,
	LaneAttributes_Sidewalk_bicyleUseAllowed = 1 << 1,
	LaneAttributes_Sidewalk_isSidewalkFlyOverLane = 1 << 2,
	LaneAttributes_Sidewalk_walkBikes = 1 << 3
} e_LaneAttributes_Sidewalk;


/** 32 DE_LaneAttributes-Striping*/
typedef enum LaneAttributes_Striping {
	LaneAttributes_Striping_stripeToConnectingLanesRevocableLane = 1 << 0,
	LaneAttributes_Striping_stripeDrawOnLeft = 1 << 1,
	LaneAttributes_Striping_stripeDrawOnRight = 1 << 2,
	LaneAttributes_Striping_stripeToConnectingLanesLeft = 1 << 3,
	LaneAttributes_Striping_stripeToConnectingLanesRight = 1 << 4,
	LaneAttributes_Striping_stripeToConnectingLanesAhead = 1 << 5
} e_LaneAttributes_Striping;

/** 33 DE_LaneAttributes-TrackedVehicle*/
typedef enum LaneAttributes_TrackedVehicle {
	LaneAttributes_TrackedVehicle_spec_RevocableLane = 1 << 0,
	LaneAttributes_TrackedVehicle_spec_commuterRailRoadTrack = 1 << 1,
	LaneAttributes_TrackedVehicle_spec_lightRailRoadTrack = 1 << 2,
	LaneAttributes_TrackedVehicle_spec_heavyRailRoadTrack = 1 << 3,
	LaneAttributes_TrackedVehicle_spec_otherRailType = 1 << 4
} e_LaneAttributes_TrackedVehicle;

/** 34 DE_LaneAttributes-Vehicle */
typedef enum LaneAttributes_Vehicle {
	LaneAttributes_Vehicle_isVehicleRevocableLane = 1 << 0,
	LaneAttributes_Vehicle_isVehicleFlyOverLane = 1 << 1,
	LaneAttributes_Vehicle_hovLaneUseOnly = 1 << 2,
	LaneAttributes_Vehicle_restrictedToBusUse = 1 << 3,
	LaneAttributes_Vehicle_restrictedToTaxiUse = 1 << 4,
	LaneAttributes_Vehicle_restrictedFromPublicUse = 1 << 5,
	LaneAttributes_Vehicle_hasIRBeaconCoverage = 1 << 6,
	LaneAttributes_Vehicle_permissionOnRequest = 1 << 7
} e_LaneAttributes_Vehicle;


/** 35 DE_LaneID*/
typedef int LaneID_t;

/** 36 DE_LaneSharing*/
typedef enum LaneSharing
{
	overlappingLaneDescriptionProvided = 1 << 0,
	multupleLanesTreatedAsOneLane = 1 << 1,
	otherNonMotorizedTrafficTypes = 1 << 2,
	individualMotorizedVehicleTraffic = 1 << 3,
	busVehicleTraffic = 1 << 4,
	taxiVehicleTraffic = 1 << 5,
	pedestriansTraffic = 1 << 6,
	cyclistVehicleTraffic = 1 << 7,
	trackedVehicleTraffic = 1 << 8,
	pedestrianTraffic = 1 << 9
}e_LaneSharing;

/** 37 DE_LaneWidth*/
typedef int LaneWidth_t;

/** 38 DE_LAtitude*/
typedef double Latitude_t;


/** 39 DE_LightState*/
typedef enum LightState {
	LightState_unaviable = 0,
	LightState_dark = 1,
	LightState_stop_then_proceed = 2,
	LightState_stop_and_remain = 3,
	LightState_pre_Movement = 4,
	LightState_permissive_Movement_Allowed = 5,
	LightState_protected_Movement_Allowed = 6,
	LightState_intersection_clearnce = 7,
	LightState_caution_Conflicting_Traffic = 8
} e_LightState;



/** 40 DE_Longitude*/
typedef double Longitude_t;

/** 41 DE_MinuteOfTheYear*/
typedef int MinuteOfTheYear_t;


/** 42 DE_MsgCount*/
typedef short MsgCount_t;


/** 43 DE_NodeID*/
typedef int NodeID_t;

/** 44 DE_OffsetLL-B12*/
typedef float OffsetLL_B12_t;


/** 50 DE_ParticipantType*/
typedef enum ParticipantType {
	ParticipantType_unknown = 0,
	ParticipantType_motor = 1,
	ParticipantType_non_motor = 2,
	ParticipantType_pedestrian = 3,
	ParticipantType_rsu = 4,
} e_ParticipantType;


/** 51 DE_PhaseID*/
typedef short PhaseID_t;

/** 52 DE_PositionConfidence*/
typedef enum PositionConfidence {
	PositionConfidence_unaviable = 0,
	PositionConfidence_a500m = 1,
	PositionConfidence_a200m = 2,
	PositionConfidence_a100m = 3,
	PositionConfidence_a50m = 4,
	PositionConfidence_a20m = 5,
	PositionConfidence_a10m = 6,
	PositionConfidence_a5m = 7,
	PositionConfidence_a2m = 8,
	PositionConfidence_a1m = 9,
	PositionConfidence_a50cm = 10,
	PositionConfidence_a20cm = 11,
	PositionConfidence_a10cm = 12,
	PositionConfidence_a5cm = 13,
	PositionConfidence_a2cm = 14,
	PositionConfidence_a1cm = 15	   
} e_PositionConfidence;

/** 53 DE_Priority*/
typedef uint8_t Priority_t;

/** 54 DE_Radius*/
typedef float Radius_t;

/** 55 DE_RadiusOfCurvation*/
typedef float RadiusOfCurvature_t;

/** 56 DE_RoadRegulatorID*/
typedef uint16_t RoadRegulatorID_t;
 
/** 57 DE_SourceType
*/
typedef enum SourceType {
	SourceType_unknown = 0,
	SourceType_selfinfo = 1,
	SourceType_v2x = 2,
	SourceType_video = 3,
	SourceType_microwaveRadar = 4,
	SourceType_loop = 5
	/*
	 * Enumeration is extensible
	 */
} e_SourceType;

/** 58 DE_Speed */
typedef float DE_Speed_t;


/** 59 DE_SpeedConfidence */
typedef enum SpeedConfidence
{
	unaviailable = 0,
	prec100ms =1,
	prec10ms = 2,
	prec5ms = 3,
	prec01ms = 4,
	prec005ms = 5,
	prec001ms = 6
}e_SpeedConfidence;


/** 60 DE_SpeedLimitType */
typedef enum SpeedLimitType
{
	SpeedLimitType_unknown = 0,
	SpeedLimitType_maxSpeedInSchoolZone = 1,
	SpeedLimitType_maxSpeedInSchoolZoneWhenChildArePresent = 2,
	SpeedLimitType_maxSpeedInConstructionZone = 3,
	SpeedLimitType_vehicleMinSpeed =4,
	SpeedLimitType_vehicleMaxSpeed =5,
	SpeedLimitType_vehicleNightMaxSpeed =6,
	SpeedLimitType_truckMinSpeed =7,
	SpeedLimitType_truckMaxSpeed = 8,
	SpeedLimitType_truckNightMaxSpeed = 9,
	SpeedLimitType_vehiclesWithTrailersMinSpeed =10,
	SpeedLimitType_vehiclesWithTrailersMaxSpeed =11,
	SpeedLimitType_vehiclesWithTrailersNightMaxSpeed = 12
}e_SpeedLimitType;

/** 61 DE_StabilityControlStatus */
typedef enum StabilityControlStatus
{
	StabilityControlStatus_unaviable =0,
	StabilityControlStatus_off =1,
	StabilityControlStatus_on = 2,
	StabilityControlStatus_engaged =3
}e_StabilityControlStatus;


/** 62 DE_SteeringWheelAngle */
typedef float DE_SteeringWheelAngle_t;


/** 63 DE_SteeringWheelAngleConfidence */
typedef enum SteeringWheelAngleConfidence
{
	SteeringWheelAngleConfidence_unaviailable = 0,
	SteeringWheelAngleConfidence_prec2deg = 1,
	SteeringWheelAngleConfidence_prec1deg = 2,
	SteeringWheelAngleConfidence_prec0_02deg = 3
}e_SteeringWheelAngleConfidence;



/** 64 DE_TimeConfidence */
typedef enum TimeConfidence
{
	time_100_000 = 0
}e_TimeConfidence;


/** 65 DE_TimeMark */
typedef int TimeMark_t;


/** 67 DE_TractionControlStatus */
typedef enum TractionControlStatus {
	TractionControlStatus_unaviable =0,
	TractionControlStatus_off =1,
	TractionControlStatus_on =2,
	TractionControlStatus_engaged =3

}e_TractionControlStatus;

/** 68 DE_TransmissionState */
typedef enum TransmissionState {
	TransmissionState_neutral = 0,
	TransmissionState_park =1,
	TransmissionState_forwardGears =2,
	TransmissionState_reverseGears =3,
	TransmissionState_reserved1 =4,
	TransmissionState_reserved2 = 5,
	TransmissionState_reserved3 = 6,
	TransmissionState_unavailable = 7
}e_TransmissionState;

/** 69 DE_VehicleEventFlags */
typedef enum VehicleEventFlags {
	VehicleEventFlags_eventHazardLights = 0,//
	VehicleEventFlags_eventStopLineViolation = 1,//
	VehicleEventFlags_eventABSactivated = 2, //
	VehicleEventFlags_eventTractionControlLoss = 3, //
	VehicleEventFlags_eventStabilityControlactivated = 4, //
	VehicleEventFlags_eventHazardousMaterials = 5, //
	VehicleEventFlags_eventReaerved1 = 6,
	VehicleEventFlags_eventHardBraking = 7,
	VehicleEventFlags_eventLightChanged = 8,
	VehicleEventFlags_eventWipersChanged = 9,
	VehicleEventFlags_eventFlatTire = 10, //
	VehicleEventFlags_eventDisabledVehicle = 11,
	VehicleEventFlags_eventAirBagDeployment = 12
}e_VehicleEventFlags;



/** 70 DE_VehicleHeight */
typedef float VehicleHeight_t;

/** 71 DE_VehicleLength */
typedef float VehicleLength_t;


/** 72 DE_VehicleWidth */
typedef float VehicleWidth_t;


/** 73-79 DE_VerticalAcceleration */
typedef float VerticalAcceleration_t;


/** 75 DE_VertOffset-B08 */
typedef float VertOffset_BX_t;

/** 80 DE_YawRate */
typedef float YawRate_t;

#endif