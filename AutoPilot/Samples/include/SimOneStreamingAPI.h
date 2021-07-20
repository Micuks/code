/*!
	@file SimOneStreamingAPI.hpp
	@author Jie.wang 2020/11/30
*/
#pragma once


#if defined(WIN32) || defined(_WIN32)
#define SIMONE_NET_API __declspec(dllexport)
#elif defined(__linux__) || defined(__linux)
#define SIMONE_NET_API __attribute__((visibility("default")))
#endif
#include <string>
#include "SimOneIOStruct.h"

#ifdef __cplusplus
extern "C"
{
#endif
	namespace SimOneSM {
		
		/*!
		\li function:
		*	GetStreamingImage
		\li brief:
		*	Get Streaming Image Data
		@param
		*	ip: UDP Streaming Image ip
		@param
		*   port: UDP Streaming Image port
		@param
		*	pImage: Image data(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetStreamingImage(const char *ip, unsigned short port, SimOne_Data_Image *pImage);
		/*!
		\li function:
		*	SetStreamingImageCB
		\li brief:
		*	Streaming Image Data update callback
		@param
		*	ip: UDP Streaming Image ip
		@param
		*   port: UDP Streaming Image port
		@param
		*	pImage: Image data(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetStreamingImageCB(const  char* ip, unsigned short port, void(*cb)(SimOne_Data_Image *pImage));
		

		/*!
		\li function:
		*	GetStreamingPointCloud
		\li brief:
		*	Get Streaming PointCloud Data
		@param
		*	ip: UDP Streaming PointCloud ip
		@param
		*   port: UDP Streaming PointCloud port
		@param
		*   infoPort: UDP Streaming device info port
		@param
		*	pPointCloud: PointCloud data(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool GetStreamingPointCloud(const  char* ip, unsigned short port, unsigned short infoPort, SimOne_Data_Point_Cloud *pPointCloud);
		/*!
		\li function:
		*	SetStreamingPointCloudUpdateCB
		\li brief:
		*	Streaming PointCloud Data update callback
		@param
		*	ip: UDP Streaming PointCloud ip
		@param
		*   port: UDP Streaming PointCloud port
		@param
		*   infoPort: UDP Streaming device info port
		@param
		*	pPointCloud: PointCloud data(output)
		@return
		*	Success or not
		*/
		SIMONE_NET_API bool SetStreamingPointCloudUpdateCB(const  char* ip, unsigned short port, unsigned short infoPort, void(*cb)(SimOne_Data_Point_Cloud *pPointCloud));

	}
#ifdef __cplusplus
}
#endif