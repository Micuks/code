cmake_minimum_required(VERSION 3.8.0)

IF (UNIX)
	set(CMAKE_C_COMPILER "/usr/bin/clang")
	set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -I/usr/include/libcxxabi")
	set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
ENDIF()

add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
 
# top project
project(SimOneIOAPISample VERSION 3.0.0 LANGUAGES C CXX)

set(THREADS_PREFER_PTHREAD_FLAG ON)

file(GLOB_RECURSE srcs *.h *.hh *i *.hpp *.c *.cc *.cpp)
# global settings
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")
SET(SIMONE_API_SAMPLE ${CMAKE_CURRENT_LIST_DIR}/..)
SET(3RDPARTY ${CMAKE_CURRENT_LIST_DIR}/../../../../3rdparty)
SET(BINARY_OUT_PATH ${SIMONE_API_SAMPLE}/bin/Release)
SET(SIMONE_PATH_ROOT ${CMAKE_CURRENT_LIST_DIR}/../../../..)
SET(BRIDGE_SM_ROOT ${CMAKE_CURRENT_LIST_DIR}/../..)

function(SetDefaultTargetProperties target)
	set_target_properties(${target} PROPERTIES
		CXX_STANDARD 14
	)
	set_target_properties(${target} PROPERTIES
		# ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../Output/lib
		# LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../Output/lib
		# RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../Output/bin
		RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../bin
	)
endfunction()

IF (WIN32)
set(LIB_DIR "${CMAKE_CURRENT_LIST_DIR}/../lib/Win64")
ELSE (UNIX)
set(LIB_DIR "${CMAKE_CURRENT_LIST_DIR}/../lib/Linux64")
ENDIF()
set(INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/../include")

option(CLOUD_PLATFORM "option for cloud build" OFF)
IF (CLOUD_PLATFORM)
	add_definitions(-DCLOUD_PLATFORM)
ENDIF(CLOUD_PLATFORM)
	
IF (CLOUD_PLATFORM)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../Workshop/LKA LKA)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../Workshop/AEB AEB)

ELSE()
#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../Autopilot/CurveSample CurveSample)
#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../Autopilot/LimitChangeLaneSample LimitChangeLaneSample)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../Autopilot/PredefinedRouteSample PredefinedRouteSample)
#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../Autopilot/TrafficLightSample TrafficLightSample)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../Workshop/AEB AEB)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../Workshop/AVP AVP)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../Workshop/LKA LKA)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../HDMap HDMap)
#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../Traffic Traffic)
#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../V2X/V2XADAS V2XADAS)
#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../V2X/V2XAPI V2XAPI)
ENDIF()





