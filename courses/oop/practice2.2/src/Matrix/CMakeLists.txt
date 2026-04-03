add_library(Matrix Matrix.cpp)

target_sources(Matrix
  PRIVATE
    Matrix.cpp
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/Matrix.h
  )

target_include_directories(Matrix
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  )
