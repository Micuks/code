add_library(Shape Shape.cpp)

target_sources(Shape
  PRIVATE
    Shape.cpp
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/Shape.h
  )

target_include_directories(Shape
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
