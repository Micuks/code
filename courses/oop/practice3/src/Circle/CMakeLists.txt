add_library(Circle Circle.cpp)

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

target_link_libraries(Circle
  PRIVATE
    Shape
    )
