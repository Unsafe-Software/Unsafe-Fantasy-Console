cmake_minimum_required(VERSION 3.8.0)
project(Unsafe-Fantasy-Console VERSION 0.0.0 LANGUAGES C CXX)

configure_file(
  "${PROJECT_SOURCE_DIR}/cfg/config.hpp.in"
  "${PROJECT_BINARY_DIR}/config.hpp"
)
include_directories("${PROJECT_BINARY_DIR}")

file(GLOB Sources src/*.c src/*.cpp)
add_executable("${PROJECT_NAME}" ${Sources})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPACK)
