#pragma once

#include "public/libexport.h"
#ifdef STATIC_SSD
	#include "SSD/public/SimVector.h"
#else
	#include "SSD/SimVector.h"
#endif
#include "MLaneId.h"

namespace HDMapStandalone {

	struct LIBEXPORT MTopoNode {
		//@brief start s value.
		double startS;
		//@brief end s value.
		double endS;
		//@brief lane ID that topo node represents
		MLaneId laneId;

		//@brief index pos list for in from all edges.
		SSD::SimVector<int> inFromAllEdge;
		//@brief index pos list for in from left side edges.
		SSD::SimVector<int> inFromLeftEdge;
		//@brief index pos list for in from right side edges.
		SSD::SimVector<int> inFromRightEdge;
		//@brief index pos list for in from predescessor edges.
		SSD::SimVector<int> inFromPreEdge;

		//@brief index pos list for out to all edges.
		SSD::SimVector<int> outToAllEdge;
		//@brief index pos list for out to left side edges.
		SSD::SimVector<int> outToLeftEdge;
		//@brief index pos list for out to right side edges.
		SSD::SimVector<int> outToRightEdge;
		//@brief index pos list for out to successor side edges.
		SSD::SimVector<int> outToSucEdge;
	};

	struct LIBEXPORT MTopoEdge {
		//@brief lane ID of from topo node.
		MLaneId fromLaneId;
		//@brief lane ID of to topo node.
		MLaneId toLaneId;
		//@brief index pos of from topo node that in topo node list.
		int fromNodePos;
		//@brief index pos of to topo node that in topo node list.
		int toNodePos;
	};

	struct LIBEXPORT MTopoGraph
	{
		//@brief topo node list.
		SSD::SimVector<MTopoNode> topoNodes;
		//@brief topo edge list.
		SSD::SimVector<MTopoEdge> topoEdges;
	};

}
