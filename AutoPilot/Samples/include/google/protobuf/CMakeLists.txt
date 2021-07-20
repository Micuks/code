#
# Created By: Qilin.Ren 2018/05/29
#

add_library(protobuf STATIC "")

find_package(Threads REQUIRED)
target_link_libraries(protobuf Threads::Threads)

include_directories("${CYBERTRON_PATH_ROOT}/3rdparty")
include_directories("${CYBERTRON_PATH_ROOT}/3rdparty/asio")
include_directories("${CYBERTRON_PATH_ROOT}/3rdparty/gtest/include")
include_directories("${CYBERTRON_PATH_ROOT}/3rdparty/gtest")

add_definitions(-DNOMINMAX)
add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)
add_definitions(-DHAVE_PTHREAD)

# set -fPIC for compile protobuf for dynamic library error in Ubuntu
if(UNIX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

set(protobuf_source_dir ${CYBERTRON_PATH_ROOT}/3rdparty/google/protobuf)
include(protobuf.cmake)
target_sources(
	protobuf PRIVATE 
	${libprotobuf_lite_files} 
	${libprotobuf_lite_includes} 
	${libprotobuf_files} 
	${libprotobuf_includes})
source_group(include FILES  
	${libprotobuf_lite_includes} 
	${libprotobuf_includes})
source_group(src FILES 
	${libprotobuf_lite_files} 
	${libprotobuf_files})

SetDefaultTargetProperties(protobuf)

IF (MSVC)
	SET_PROPERTY(TARGET protobuf PROPERTY FOLDER "3rdParty")
ENDIF()

# Turn off warnings
if(MSVC)
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W0" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W0")
  endif()
elseif(UNIX)
  # Update if necessary
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

