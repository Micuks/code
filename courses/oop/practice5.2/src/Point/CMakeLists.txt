add_library(Point Point.cpp)

target_sources(Point
  PRIVATE
    Point.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Point.h
  )

target_include_directories(Point
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    )
