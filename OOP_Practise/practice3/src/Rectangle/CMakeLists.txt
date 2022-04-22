add_library(Rectangle Rectangle.cpp)

target_sources(Rectangle
  PRIVATE
    Rectangle.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Rectangle.h
  )

target_include_directories(Rectangle
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

target_link_libraries(Rectangle
  PRIVATE
    Shape
    )
