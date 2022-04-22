add_executable(practice2 main.cpp)

add_subdirectory(./Point)
add_subdirectory(./Circle)

target_link_libraries(practice2
  PRIVATE
    Circle
    Point
    )
