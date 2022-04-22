add_library(Cube Cube.cpp)

target_sources(Cube
  PRIVATE
    Cube.cpp
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/Cube.h
    )

target_include_directories(Cube
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  )

target_link_libraries(Cube
  PRIVATE
    Rectangle
    Shape
    )
