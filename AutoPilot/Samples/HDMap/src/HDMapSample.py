import os
import pySimOneIO
import time

from SimOneIOStruct import *

CLOUD_PLATFORM = 0
M_PI = 3.14159265358979323846

# Global
PosX = 0;
PosY = 0;
PosZ = 0;


def SampleGetNearMostLane(pos):
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "SampleGetNearMostLane:")
	else:
		print("SampleGetNearMostLane:")
	info = pySimOneIO.getNearMostLane(pos)
	if info.exists == False:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "Not exists!")
		else:
			print("Not exists!")
		return
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "lane id:%s" % info.laneId.GetString())
	else:
		print("lane id:", info.laneId.GetString())
	return info.laneId


def SampleGetNearLanes(pos, radius):
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "SampleGetNearLanes:")
	else:
		print("SampleGetNearLanes:")
	nearLanesInfo = pySimOneIO.getNearLanes(pos, radius)
	if nearLanesInfo.exists == False:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "Not exists!")
		else:
			print("Not exists!")
		return
	lanesInfo = nearLanesInfo.laneIdList
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "lanesInfo size:%s" % lanesInfo.Size())
		SoBridgeLogOutput(0, "lanesInfo id list:")
	else:
		print("lanesInfo size:", lanesInfo.Size())
		print("lanesInfo id list:")
	for i in range(lanesInfo.Size()):
		element = lanesInfo.GetElement(i)
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "%s" % element.GetString())
			SoBridgeLogOutput(0, ",")
		else:
			print(element.GetString())
			print(",")


def SampleGetNearLanesWithAngle(pos, radius, headingAngle, shiftAngle):
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "SampleGetNearLanesWithAngle:")
	else:
		print("SampleGetNearLanesWithAngle:")
	nearLanesInfo = pySimOneIO.getNearLanesWithAngle(pos, radius, headingAngle, shiftAngle)
	if nearLanesInfo.exists == False:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "Not exists!")
		else:
			print("Not exists!")
		return
	lanesInfo = nearLanesInfo.laneIdList
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "lanesInfo size:%s"%lanesInfo.Size())
		SoBridgeLogOutput(0, "lanesInfo id list:")
	else:
		print("lanesInfo size:", lanesInfo.Size())
		print("lanesInfo id list:")
	for i in range(lanesInfo.Size()):
		element = lanesInfo.GetElement(i)
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "%s" % element.GetString())
			SoBridgeLogOutput(0, ",")
		else:
			print(element.GetString())
			print(",")


def SampleGetDistanceToLaneBoundary(pos):
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "SampleGetDistanceToLaneBoundary:")
	else:
		print("SampleGetDistanceToLaneBoundary:")
	distanceToLaneBoundaryInfo = pySimOneIO.getDistanceToLaneBoundary(pos);
	if distanceToLaneBoundaryInfo.exists == False:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "Not exists!")
		else:
			print("Not exists!")
		return

	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "laneId:%s" % distanceToLaneBoundaryInfo.laneId.GetString())
		SoBridgeLogOutput(0, "distToLeft:%s" % distanceToLaneBoundaryInfo.distToLeft)
		SoBridgeLogOutput(0, "distToRight:%s" % distanceToLaneBoundaryInfo.distToRight)
		SoBridgeLogOutput(0, "distToLeft2D:%s" % distanceToLaneBoundaryInfo.distToLeft2D)
		SoBridgeLogOutput(0, "distToRight2D:%s" % distanceToLaneBoundaryInfo.distToRight2D)
	else:
		print("laneId:", distanceToLaneBoundaryInfo.laneId.GetString())
		print("distToLeft:", distanceToLaneBoundaryInfo.distToLeft)
		print("distToRight:", distanceToLaneBoundaryInfo.distToRight)
		print("distToLeft2D:", distanceToLaneBoundaryInfo.distToLeft2D)
		print("distToRight2D:", distanceToLaneBoundaryInfo.distToRight2D)


def SampleGetLaneSample(laneId):
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "SampleGetLaneSample:")
	else:
		print("SampleGetLaneSample:")
	sampleInfo = pySimOneIO.getLaneSample(laneId)
	if sampleInfo.exists == False:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "Not exists!")
		else:
			print("Not exists!")
		return
	leftBoundary = sampleInfo.laneInfo.leftBoundary

	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "leftBoundary knot size:%s"%leftBoundary.Size())
		SoBridgeLogOutput(0, "leftBoundary knot list:")
	else:
		print("leftBoundary knot size:", leftBoundary.Size())
		print("leftBoundary knot list:")
	for i in range(leftBoundary.Size()):
		element = leftBoundary.GetElement(i)
		print("(", element.x, ",", element.y, ",", element.z, "),")

	rightBoundary = sampleInfo.laneInfo.rightBoundary

	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "rightBoundary knot size:%s"%rightBoundary.Size())
		SoBridgeLogOutput(0, "rightBoundary knot list:")
	else:
		print("rightBoundary knot size:", rightBoundary.Size())
		print("rightBoundary knot list:")

	for i in range(rightBoundary.Size()):
		element = rightBoundary.GetElement(i)
		print("(", element.x, ",", element.y, ",", element.z, "),")

	centerLine = sampleInfo.laneInfo.centerLine

	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "centerLine knot size:%s"%centerLine.Size())
		SoBridgeLogOutput(0, "centerLine knot list:")
	else:
		print("centerLine knot size:", centerLine.Size())
		print("centerLine knot list:")

	for i in range(centerLine.Size()):
		element = centerLine.GetElement(i)
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "(%s,%s,%s)" % element.x,element.y,element.z)
			SoBridgeLogOutput(0, "centerLine knot list:")
		else:
			print("(", element.x, ",", element.y, ",", element.z, "),")


def SampleGetLaneLink(laneId):
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "SampleGetLaneLink:")
	else:
		print("SampleGetLaneLink:")
	laneLinkInfo = pySimOneIO.getLaneLink(laneId)
	if laneLinkInfo.exists == False:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "Not exists!")
		else:
			print("Not exists!")
		return
	laneLink = laneLinkInfo.laneLink
	predecessorIds = laneLink.predecessorLaneIds

	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "predecessorLaneIds size:%ds"%predecessorIds.Size())
	else:
		print("predecessorLaneIds size:", predecessorIds.Size())
	if predecessorIds.Size() > 0:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "predecessorLaneIds:")
		else:
			print("predecessorLaneIds:")
	for i in range(predecessorIds.Size()):
		element = predecessorIds.GetElement(i)
		print(element.GetString())
	successorIds = laneLink.successorLaneIds

	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "successorLaneIds size:%s"%successorIds.Size())
	else:
		print("successorLaneIds size:", successorIds.Size())
	if successorIds.Size() > 0:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "successorLaneIds:")
		else:
			print("successorLaneIds:")
	for i in range(successorIds.Size()):
		element = successorIds.GetElement(i)
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "%s"%element.GetString())
		else:
			print(element.GetString())
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "leftNeighborLaneId:%s"%laneLink.leftNeighborLaneId.GetString())
		SoBridgeLogOutput(0, "rightNeighborLaneId:%s" % laneLink.rightNeighborLaneId.GetString())
	else:
		print("leftNeighborLaneId:", laneLink.leftNeighborLaneId.GetString())
		print("rightNeighborLaneId:", laneLink.rightNeighborLaneId.GetString())


def SampleGetLaneType(laneId):
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "SampleGetLaneType:")
	else:
		print("SampleGetLaneType:")
	laneType = pySimOneIO.getLaneType(laneId)
	if laneType.exists == False:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "Not exists!")
		else:
			print("Not exists!")
		return
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "lane type:%s"%laneType.laneType)
	else:
		print("lane type:", laneType.laneType)


def SampleGetLaneWidth(laneId, pos):
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "SampleGetLaneWidth:")
	else:
		print("SampleGetLaneWidth:")
	laneWidthInfo = pySimOneIO.getLaneWidth(laneId, pos)
	if laneWidthInfo.exists == False:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "Not exists!")
		else:
			print("Not exists!")
		return
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "lane width:%s"%laneType.width)
	else:
		print("lane width:", laneWidthInfo.width)


def SampleGetLaneST(laneId, pos):
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "SampleGetLaneST:")
	else:
		print("SampleGetLaneST:")
	stInfo = pySimOneIO.getLaneST(laneId, pos)
	if stInfo.exists == False:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "Not exists!")
		else:
			print("Not exists!")
		return
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "[%s,%s] relative to this lane:"%(stInfo.s,stInfo.t))
	else:
		print("[s,t] relative to this lane:", stInfo.s, ",", stInfo.t)


def SampleGetRoadST(laneId, pos):
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "SampleGetRoadST:")
	else:
		print("SampleGetRoadST:")
	stzInfo = pySimOneIO.getRoadST(laneId, pos)
	if stzInfo.exists == False:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "Not exists!")
		else:
			print("Not exists!")
		return
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "[%s,%s] relative to this road:"%(stInfo.s,stInfo.t))
		SoBridgeLogOutput(0, "height of input point:%s" %stzInfo.z)
	else:
		print("[s,t] relative to this road:", stzInfo.s, ",", stzInfo.t)
		print("height of input point:", stzInfo.z)


def SampleGetInertialFromLaneST(laneId, s, t):
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "SampleGetInertialFromLaneST:")
	else:
		print("SampleGetInertialFromLaneST:")
	inertialFromLaneSTInfo = pySimOneIO.getInertialFromLaneST(laneId, s, t)
	if inertialFromLaneSTInfo.exists == False:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "Not exists!")
		else:
			print("Not exists!")
		return

	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "inertial vector: (%s,%s,%s)"%(inertialFromLaneSTInfo.inertial.x,inertialFromLaneSTInfo.inertial.y,inertialFromLaneSTInfo.inertial.z))
		SoBridgeLogOutput(0, "dir vector: (%s,%s,%s)"%(inertialFromLaneSTInfo.dir.x,inertialFromLaneSTInfo.dir.y,inertialFromLaneSTInfo.dir.z))
	else:
		print("inertial vector: (", inertialFromLaneSTInfo.inertial.x, ",", inertialFromLaneSTInfo.inertial.y, ",", inertialFromLaneSTInfo.inertial.z, "),")
		print("dir vector: (", inertialFromLaneSTInfo.dir.x, ",", inertialFromLaneSTInfo.dir.y, ",", inertialFromLaneSTInfo.dir.z, "),")


def SampleContainsLane(laneId):
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "SampleContainsLane:")
	else:
		print("SampleContainsLane:")
	ret = pySimOneIO.containsLane(laneId)
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "return state:%s"%ret)
	else:
		print("return state:", ret)


def SampleGetParkingSpaceList():
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "SampleGetParkingSpaceList:")
	else:
		print("SampleGetParkingSpaceList:")
	parkingSpaceList = pySimOneIO.getParkingSpaceList()

	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "parkingSpace count:%d"%parkingSpaceList.Size())
	else:
		print("parkingSpace count:", parkingSpaceList.Size())
	for i in range(parkingSpaceList.Size()):
		parkingSpace = parkingSpaceList.GetElement(i)
		front = parkingSpace.front
		knots = parkingSpace.boundaryKnots
		knot0 = knots.GetElement(0)

		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "parkingSpace count:%s" % parkingSpaceList.Size())
			SoBridgeLogOutput(0,"parkingSpace id:%s"%parkingSpace.id)
			SoBridgeLogOutput(0,"roadMark at which side:%s"%front.side.GetString())
			SoBridgeLogOutput(0,"roadMark type:%s"%front.type)
			SoBridgeLogOutput(0,"roadMark color:%s"%front.color)
			SoBridgeLogOutput(0,"roadMark width:%s"%front.width)
			SoBridgeLogOutput(0,"boundaryKnots count:%s"%knots.Size())
			SoBridgeLogOutput(0,"knot0 point: (%s,%s,%s)"%(knot0.x, knot0.y, knot0.z))

		else:
			print("parkingSpace id:", parkingSpace.id)
			print("roadMark at which side:", front.side.GetString())
			print("roadMark type:", front.type)
			print("roadMark color:", front.color)
			print("roadMark width:", front.width)
			print("boundaryKnots count:", knots.Size())
			print("knot0 point: (", knot0.x, ",", knot0.y, ",", knot0.z, ")")


def SampleGetPredefinedRoute():
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "SampleGetPredefinedRoute:")
	else:
		print("SampleGetPredefinedRoute:")
	routeInfo = pySimOneIO.getPredefinedRoute()
	if routeInfo.exists == False:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "Not exists!")
		else:
			print("Not exists!")
		return

	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "route point count:%s"%routeInfo.route.Size())
	else:
		print("route point count:", routeInfo.route.Size())
	for i in range(routeInfo.route.Size()):
		pt = routeInfo.route.GetElement(i)
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "route point: (%s,%s,%s)" % (pt.x,pt.y,pt.z))
		else:
			print("route point: (", pt.x, ",", pt.y, ",", pt.z, "),")


def SampleNavigate(inputPoints):
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "SampleNavigate:")
	else:
		print("SampleNavigate:")
	navigateInfo = pySimOneIO.navigate(inputPoints)
	if navigateInfo.exists == False:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "Not exists!")
		else:
			print("Not exists!")
		return
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "roadIdListcount:%s"%navigateInfo.roadIdList.Size())
	else:
		print("roadIdList count:", navigateInfo.roadIdList.Size())

	for i in range(navigateInfo.roadIdList.Size()):
		roadId = navigateInfo.roadIdList.GetElement(i)
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "roadId:%s" %roadId)
		else:
			print("roadId:", roadId)

	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "indexOfValidPoints count:%s"%navigateInfo.indexOfValidPoints.Size())
	else:
		print("indexOfValidPoints count:", navigateInfo.indexOfValidPoints.Size())
	for i in range(navigateInfo.indexOfValidPoints.Size()):
		index = navigateInfo.indexOfValidPoints.GetElement(i)
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "index:%s" % index)
		else:
			print("index:", index)


def SampleGetRoadMark(pos, laneId):
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "SampleGetRoadMark:")
	else:
		print("SampleGetRoadMark:")
	roadMarkInfo = pySimOneIO.getRoadMark(pos, laneId)
	if roadMarkInfo.exists == False:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "Not exists!")
		else:
			print("Not exists!")
		return
	left = roadMarkInfo.left
	right = roadMarkInfo.right

	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0,"left roadMark sOffset:%s"%left.sOffset)
		SoBridgeLogOutput(0,"left roadMark type:%s"% left.type)
		SoBridgeLogOutput(0,"left roadMark color:%s"% left.color)
		SoBridgeLogOutput(0,"left roadMark width:%s"% left.width)
		SoBridgeLogOutput(0,"right roadMark sOffset:%s"% right.sOffset)
		SoBridgeLogOutput(0,"right roadMark type:%s"% right.type)
		SoBridgeLogOutput(0,"right roadMark color:%s"% right.color)
		SoBridgeLogOutput(0,"right roadMark width:%s"% right.width)
	else:
		print("left roadMark sOffset:", left.sOffset)
		print("left roadMark type:", left.type)
		print("left roadMark color:", left.color)
		print("left roadMark width:", left.width)
		print("right roadMark sOffset:", right.sOffset)
		print("right roadMark type:", right.type)
		print("right roadMark color:", right.color)
		print("right roadMark width:", right.width)


def SampleGetTrafficLightList():
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "SampleGetTrafficLightList:")
	else:
		print("SampleGetTrafficLightList:")
	trafficLightList = pySimOneIO.getTrafficLightList()

	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "trafficLight count:%s"%trafficLightList.Size())
	else:
		print("trafficLight count:", trafficLightList.Size())
	for i in range(trafficLightList.Size()):
		light = trafficLightList.GetElement(i)
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "light id:%s"% light.id)
			SoBridgeLogOutput(0, "light type:%s"% light.type.GetString())
			SoBridgeLogOutput(0, "light isDynamic:%s"% light.isDynamic)
			SoBridgeLogOutput(0, "validity count:%a"%light.validities.Size())
		else:
			print("light id:", light.id)
			print("light type:", light.type.GetString())
			print("light isDynamic:", light.isDynamic)
			print("validity count:", light.validities.Size())
		for j in range(light.validities.Size()):
			validity = light.validities.GetElement(j)

			if CLOUD_PLATFORM:
				SoBridgeLogOutput(0,"validity roadId:%s"% validity.roadId)
				SoBridgeLogOutput(0,"validity fromLaneId:%s"% validity.fromLaneId)
				SoBridgeLogOutput(0,"validity toLaneId:%s"%validity.toLaneId)
			else:
				print("validity roadId:", validity.roadId)
				print("validity fromLaneId:", validity.fromLaneId)
				print("validity toLaneId:", validity.toLaneId)


def SampleGetTrafficSignList():
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "SampleGetTrafficSignList:")
	else:
		print("SampleGetTrafficSignList:")
	trafficSignList = pySimOneIO.getTrafficSignList()

	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "trafficSign count:%s"% trafficSignList.Size())
	else:
		print("trafficSign count:", trafficSignList.Size())
	for i in range(trafficSignList.Size()):
		sign = trafficSignList.GetElement(i)
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0,"sign id:%s"%sign.id)
			SoBridgeLogOutput(0,"sign type:%s"%sign.type.GetString())
			SoBridgeLogOutput(0,"sign isDynamic:%s"% sign.isDynamic)
			SoBridgeLogOutput(0,"validity count:%s"% sign.validities.Size())
		else:
			print("sign id:", sign.id)
			print("sign type:", sign.type.GetString())
			print("sign isDynamic:", sign.isDynamic)
			print("validity count:", sign.validities.Size())
		for j in range(sign.validities.Size()):
			validity = sign.validities.GetElement(j)

			if CLOUD_PLATFORM:
				SoBridgeLogOutput(0,"validity roadId:%s"% validity.roadId)
				SoBridgeLogOutput(0,"validity fromLaneId:%s"% validity.fromLaneId)
				SoBridgeLogOutput(0,"validity toLaneId:%s"% validity.toLaneId)
			else:
				print("validity roadId:", validity.roadId)
				print("validity fromLaneId:", validity.fromLaneId)
				print("validity toLaneId:", validity.toLaneId)

def SampleGetStoplineList(laneId):
	pt = pySimOneIO.pySimPoint3D(-16,60.63,0)
	info = pySimOneIO.getNearMostLane(pt)
	if info.exists == False:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "Can't find near most lane for input point!")
		else:
			print("Can't find near most lane for input point!")
		return
	trafficLightList = pySimOneIO.getTrafficLightList()
	if trafficLightList.Size() < 1:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0,"No traffic light exists!")
		else:
			print("No traffic light exists!")
		return
	light0 = trafficLightList.GetElement(0)
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "SampleGetStoplineList:")
	else:
		print("SampleGetStoplineList:")
	stoplineList = pySimOneIO.getStoplineList(light0, laneId)

	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "stopline count:%s"%stoplineList.Size())
	else:
		print("stopline count:", stoplineList.Size())
	for i in range(stoplineList.Size()):
		stopline = stoplineList.GetElement(i)

		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "stopline id:%s"% stopline.id)
		else:
			print("stopline id:", stopline.id)

def SampleGetCrosswalkList():
	pt=pySimOneIO.pySimPoint3D(-16,60.63,0)
	info=pySimOneIO.getNearMostLane(pt)
	if info.exists == False:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "Can't find near most lane for input point!")
		else:
			print("Can't find near most lane for input point!")
		return
	trafficLightList = pySimOneIO.getTrafficLightList()
	if trafficLightList.Size() < 1:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "No traffic light exists!")
		else:
			print("No traffic light exists!")
		return
	light0 = trafficLightList.GetElement(0)
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "SampleGetCrosswalkList:")
	else:
		print("SampleGetCrosswalkList:")
	crosswalkList = pySimOneIO.getCrosswalkList(light0, info.laneId)

	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "crosswalk count:%s"% crosswalkList.Size())
	else:
		print("crosswalk count:", crosswalkList.Size())
	for i in range(crosswalkList.Size()):
		crosswalk = crosswalkList.GetElement(i)
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "crosswalk id:%s"% crosswalk.id)
		else:
			print("crosswalk id:", crosswalk.id)

def SampleGetCrossHatchList():
	pt=pySimOneIO.pySimPoint3D(-16,60.63,0)
	info=pySimOneIO.getNearMostLane(pt)
	if info.exists == False:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "Can't find near most lane for input point!")
		else:
			print("Can't find near most lane for input point!")
		return
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0,"SampleGetCrossHatchList:")
	else:
		print("SampleGetCrossHatchList:")
	crossHatchList = pySimOneIO.getCrossHatchList(info.laneId)

	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0,"crossHatch count:%s"% crossHatchList.Size())
	else:
		print("crossHatch count:", crossHatchList.Size())
	for i in range(crossHatchList.Size()):
		crossHatch = crossHatchList.GetElement(i)

		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "crossHatch id:%s"% crossHatch.id)
		else:
			print("crossHatch id:", crossHatch.id)

def SampleGetLaneMiddlePoint(pos, laneId):
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "SampleGetLaneMiddlePoint:")
	else:
		print("SampleGetLaneMiddlePoint:")
	laneMiddlePointInfo = pySimOneIO.getLaneMiddlePoint(pos, laneId)
	if laneMiddlePointInfo.exists == False:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "Not exists!")
		else:
			print("Not exists!")
		return

	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "targetPoint vector: (%s,%s,%s)"%(laneMiddlePointInfo.targetPoint.x,laneMiddlePointInfo.targetPoint.y,laneMiddlePointInfo.targetPoint.z))
		SoBridgeLogOutput(0, "dir vector: (%s,%s,%s)"%laneMiddlePointInfo.dir.x,laneMiddlePointInfo.dir.y,laneMiddlePointInfo.dir.z)
	else:
		print("targetPoint vector: (", laneMiddlePointInfo.targetPoint.x, ",", laneMiddlePointInfo.targetPoint.y, ",", laneMiddlePointInfo.targetPoint.z, "),")
		print("dir vector: (", laneMiddlePointInfo.dir.x, ",", laneMiddlePointInfo.dir.y, ",", laneMiddlePointInfo.dir.z, "),")

def SampleGetHeights(pos):
	HeightsInfo = pySimOneIO.getHeights(pos, 10.0)
	if HeightsInfo.exists == False:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "Not exists!")
		else:
			print("Not exists!")
		return
	for i in range(HeightsInfo.heights.Size()):

		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "heights = %s" % HeightsInfo.heights.GetElement(i))
		else:
			print("heights = %s" % HeightsInfo.heights.GetElement(i))
	for i in range(HeightsInfo.roadIdList.Size()):

		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "roadId = %s" % HeightsInfo.roadIdList.GetElement(i))
		else:
			print("roadId = %s" % HeightsInfo.roadIdList.GetElement(i))
	for i in range(HeightsInfo.insideRoadStates.Size()):

		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "insideRoadState = %s" % HeightsInfo.insideRoadStates.GetElement(i))
		else:
			print("insideRoadState = %s" % HeightsInfo.insideRoadStates.GetElement(i))


def SampleGenerateRoute():
	inputPts = pySimOneIO.pySimPoint3DVector()
	pt1 = pySimOneIO.pySimPoint3D(-194.625, -6.500037, 0)
	pt2 = pySimOneIO.pySimPoint3D(172.493987, -2.731247, 0)
	inputPts.AddElement(pt1)
	inputPts.AddElement(pt2)
	generateRouteInfo = pySimOneIO.generateRoute(inputPts)
	if generateRouteInfo.exists == False:
		if CLOUD_PLATFORM:
			SoBridgeLogOutput(0, "Not exists!")
		else:
			print("Not exists!")
		return
	indexOfValidPoints = generateRouteInfo.indexOfValidPoints

	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "indexOfValidPoints.Size() = %s" % indexOfValidPoints.Size())
	else:
		print("indexOfValidPoints.Size() = %s" % indexOfValidPoints.Size())
	route = generateRouteInfo.route

	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "route = %s" % route.Size())
	else:
		print("route = %s" % route.Size())


def gpsCB(mainVehicleId, data):
	global PosX, PosY, PosZ
	PosX = data[0].posX
	PosY = data[0].posY
	PosZ = data[0].posZ
	#print("gpsCB: V:{0} X:{1} Y:{2} Z:{3}".format(mainVehicleId, PosX, PosY, PosZ))


def Samples(pos):
	#1. SampleGetNearMostLane
	laneId = SampleGetNearMostLane(pos)
	#2. SampleGetNearLanes
	SampleGetNearLanes(pos, 5)
	#3. SampleGetNearLanesWithAngle
	headingAngle = 30 / 180 * M_PI
	shiftAngle = 90 / 180 * M_PI
	SampleGetNearLanesWithAngle(pos, 5, headingAngle, shiftAngle)
	#4. GetDistanceToLaneBoundary
	SampleGetDistanceToLaneBoundary(pos)
	#5. GetLaneSample
	SampleGetLaneSample(laneId)
	#6. GetLaneLink
	SampleGetLaneLink(laneId)
	#7. GetLaneType
	SampleGetLaneType(laneId)
	#8. GetLaneWidth
	SampleGetLaneWidth(laneId, pos)
	#9. GetLaneST
	SampleGetLaneST(laneId, pos)
	#10. GetRoadST
	SampleGetRoadST(laneId, pos)
	#11. ContainsLane
	SampleContainsLane(laneId)
	#12. GetCrossHatchList
	SampleGetCrossHatchList()
	#13. GetTrafficLightList
	SampleGetTrafficLightList()
	#14. GetCrosswalkList
	SampleGetCrosswalkList()
	#15. GetHeights
	SampleGetHeights(pos)
	#16. GetInertialFromLaneST
	SampleGetInertialFromLaneST(laneId, 0, -3.5)
	#17. GetLaneMiddlePoint
	SampleGetLaneMiddlePoint(pos, laneId)
	#18. GetParkingSpaceList
	SampleGetParkingSpaceList()
	#19. GetPredefinedRoute
	SampleGetPredefinedRoute()
	#20. GetRoadMark
	SampleGetRoadMark(pos, laneId)
	#21. GetStoplineList
	SampleGetStoplineList(laneId)
	#22. GetTrafficSignList
	SampleGetTrafficSignList()
	#23. Navigate
	inputPoints = pySimOneIO.pySimPoint3DVector()
	pt1 = pySimOneIO.pySimPoint3D(562.7,531.4,0)
	pt2 = pySimOneIO.pySimPoint3D(837.9,618.4,0)
	inputPoints.AddElement(pt1)
	inputPoints.AddElement(pt2)
	SampleNavigate(inputPoints)
	# 24. GenerateRoute
	SampleGenerateRoute()
	
def main():
	#usage. Test api online with SimOne
	SoApiStart()
	ret = pySimOneIO.loadHDMap(100)
	if CLOUD_PLATFORM:
		SoBridgeLogOutput(0, "Load xodr success:", ret)
	else:
		print("Load xodr success:", ret)

	#pos = pySimOneIO.pySimPoint3D(-5.41140, 156.28286, -0.53761)

	SoApiSetGpsUpdateCB(gpsCB)

	while (1):
		if PosX != 0:
			# print("gpsCB:  X:{0} Y:{1} Z:{2}".format( PosX, PosY, PosZ))
			pos = pySimOneIO.pySimPoint3D(PosX, PosY, PosZ)
			Samples(pos)
			time.sleep(2)

if __name__ == '__main__':
	main()

