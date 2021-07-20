#ifndef Message_H_
#define  Message_H_

#include "DataElement.hpp"
#include "DataFrame.hpp"

namespace V2X {

	/** 1 MessageFrame */
	typedef struct BasicSafetyMessage
	{
		MsgCount_t msgCnt; 
		int id;
		int plateNo;
		DSecond_t secMark;
		f_Position3D pos;
		f_PositionConfidenceSet accuracy;
		e_TransmissionState transmisson;
		DE_Speed_t speed;
		Heading_t heading;
		DE_SteeringWheelAngle_t angle; 
		f_MontionConfidenceSet motionCfd;
		f_AccelerationSet4Way accelSet;
		f_BrakeSystemStatus brakes;
		f_VehicleSize size;
		f_VehicleClassification vehicleClass;
		f_VehicleSafetyExtension safetyExt;
	}m_BasicSafetyMessage;


	/** 2 MapData */
	typedef struct MapData {
		MsgCount_t msgCnt;
		MinuteOfTheYear_t timeStamp;
		NodeList_t nodes;
	}m_MapData;

	/** 3 RoadSideInformation */
	typedef struct RoadSideInformation
	{
		MsgCount_t msgCnt;
		MinuteOfTheYear_t timeStamp;
		int id;
		int rsiId;
		AlertType_t alertType;
		DescriptiveName_t description;
		Priority_t priority;
		f_Position3D refPos;
		PathPointList_t alertPath;
		Radius_t alertRadius;
	}m_RoadSideInformation;

	/** 4 RoadsideSafetyMessage	 */
	typedef struct RoadsideSafetyMessage
	{
		MsgCount_t msgCnt;
		int id;
		f_Position3D refPos;
		ParticipantList_t participaints;
	}m_RoadsideSafetyMessage;

	/** 5 SPAT */
	typedef struct SPAT
	{
		MsgCount_t msgCnt;
		MinuteOfTheYear_t timeStamp;
		DescriptiveName_t name; //OPTIONAL
		IntersectionStateList_t intersections;
	}m_SPAT;

	typedef struct MessageFrame
	{
		m_BasicSafetyMessage bsmFrame;
		m_MapData mapFrame;
		m_RoadsideSafetyMessage rsmFrame;
		m_SPAT spatFrame;
		m_RoadSideInformation rsiFrame;
	}mf_MessageFrame;
}

#endif // !Message_H_