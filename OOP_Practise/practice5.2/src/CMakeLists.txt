add_subdirectory(Point)

add_executable(practice5.2
  main.cpp
  )

target_link_libraries(practice5.2
  PUBLIC
    Point
    )
