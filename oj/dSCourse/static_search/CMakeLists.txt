cmake_minimum_required(VERSION 3.5)

project(search)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")

set (CMAKE_BUILD_TYPE debug)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

aux_source_directory(src DIR_SRCS)

add_executable(search ${DIR_SRCS})
