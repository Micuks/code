cmake_minimum_required(VERSION 3.5)

project(tree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")

set (CMAKE_BUILD_TYPE debug)

set(CMAKE_CXX_STANDARD 11)

include_directories(inclde)

aux_source_directory(src DIR_SRCS)

add_executable(tree ${DIR_SRCS})
