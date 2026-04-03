add_subdirectory(Shape)
add_subdirectory(Rectangle)
add_subdirectory(Cube)
add_subdirectory(Circle)

add_executable(practice3 main.cpp)

target_link_libraries(practice3
  PUBLIC
  Shape
  Rectangle
  Cube
  Circle
  )
