add_executable(practice3 main.cpp)

add_subdirectory(Matrix)

target_link_libraries(practice3
  PRIVATE
  Matrix
  )
