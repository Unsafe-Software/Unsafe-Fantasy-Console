cmake_minimum_required(VERSION 3.8.0)
project(Unsafe-Fantasy-Console VERSION 0.0.0 LANGUAGES C CXX)
set (CMAKE_CXX_STANDARD 11)

# --- Config ---
configure_file(
  "${PROJECT_SOURCE_DIR}/cfg/config.hpp.in"
  "${PROJECT_BINARY_DIR}/config.hpp"
)
include_directories("${PROJECT_BINARY_DIR}")

# --- Compile bootstrap.lua ---
execute_process(
  COMMAND xxd -i bootstrap.ufc src/bootstrap.ufc.h
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# --- Libraries ---
include(FetchContent)
# Raylib
FetchContent_Declare(
  raylib
  GIT_REPOSITORY "https://github.com/raysan5/raylib"
  GIT_TAG "5.0"
)
FetchContent_MakeAvailable(raylib)
# Lua
FetchContent_Declare(
    lua
    GIT_REPOSITORY "https://github.com/marovira/lua"
    GIT_TAG "5.4.4"
)
FetchContent_MakeAvailable(lua)

# --- Executables ---
file(GLOB Sources src/*.c src/*.cpp)
add_compile_definitions("RELEASE=$<CONFIG:Release>")
add_executable("${PROJECT_NAME}" ${Sources})
target_link_libraries("${PROJECT_NAME}" raylib lua::lua)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPACK)
