add_library(Circle "")

target_link_libraries(Circle
  PRIVATE
    Point
  )

target_sources(Circle
  PRIVATE
    Circle.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Circle.h
  )

target_include_directories(Circle
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  )
