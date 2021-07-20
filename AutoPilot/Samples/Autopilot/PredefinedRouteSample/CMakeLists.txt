
# set(CMAKE_C_COMPILER "/usr/local/gcc")
# set(CMAKE_CXX_COMPILER "/usr/bin/g++")

add_executable(PredefinedRoute "")


file(GLOB_RECURSE srcs *.h *.hh *i *.hpp *.c *.cc *.cpp *.py)
file(GLOB_RECURSE headers *.h)

target_sources(PredefinedRoute PRIVATE "src/PredefinedRouteSample.cpp" ${headers})


source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${srcs})

# include_directories("${SIMONE_API}/include/")
include_directories("${CMAKE_CURRENT_LIST_DIR}/include/")
include_directories("${INCLUDE_DIR}")
#include_directories("${3RDPARTY}")

# find_package(OpenCV REQUIRED)
# target_link_libraries(image ${OpenCV_LIBS})

IF (WIN32)
	add_definitions(-D_WIN32_WINNT=0x0501)
ENDIF()
	add_definitions(-DNOMINMAX)
	add_definitions(-DUNICODE)
	add_definitions(-D_UNICODE)

IF (MSVC)
	string(REPLACE "/MDd" "/MD" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
ENDIF()

SetDefaultTargetProperties(PredefinedRoute)


IF (WIN32)
		target_link_libraries(PredefinedRoute  ${LIB_DIR}/SimOneIOAPI.lib ${LIB_DIR}/SSD.lib ${LIB_DIR}/HDMapModule.lib  ${LIB_DIR}/ProtobufModule.lib)

	
	add_custom_command(TARGET PredefinedRoute
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${LIB_DIR}/SimOneIOAPI.dll ${BINARY_OUT_PATH}/SimOneIOAPI.dll
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${LIB_DIR}/SSD.dll ${BINARY_OUT_PATH}/SSD.dll
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${LIB_DIR}/HDMapModule.dll ${BINARY_OUT_PATH}/HDMapModule.dll
        )

ELSEIF (UNIX)
        # target_link_libraries(image_cv debug ${OpenCV_LIBS})
        # target_link_libraries(image_cv optimized ${OpenCV_LIBS})

	target_link_libraries(PredefinedRoute debug ${LIB_DIR}/libSimOneIOAPI.so)
        target_link_libraries(PredefinedRoute optimized ${LIB_DIR}/libSimOneIOAPI.so -lpthread)
        target_link_libraries(PredefinedRoute debug /usr/lib/x86_64-linux-gnu/libcurl.so.4)
        target_link_libraries(PredefinedRoute optimized /usr/lib/x86_64-linux-gnu/libcurl.so.4)
        target_link_libraries(PredefinedRoute debug ${LIB_DIR}/libSSD.so)
        target_link_libraries(PredefinedRoute optimized ${LIB_DIR}/libSSD.so -lpthread)
        target_link_libraries(PredefinedRoute debug ${LIB_DIR}/libHDMapModule.so)
        target_link_libraries(PredefinedRoute optimized ${LIB_DIR}/libHDMapModule.so)
    
        add_custom_command(TARGET PredefinedRoute
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${LIB_DIR}/libSimOneIOAPI.so ${BINARY_OUT_PATH}/libSimOneIOAPI.so
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${LIB_DIR}/libSSD.so ${BINARY_OUT_PATH}/libSSD.so
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${LIB_DIR}/libHDMapModule.so ${BINARY_OUT_PATH}/libHDMapModule.so
        )
ENDIF()