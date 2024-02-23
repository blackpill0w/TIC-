cmake_minimum_required(VERSION 3.14)
project(TIC++ CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
string(CONCAT CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS}"
  " -Wall -Wextra"
  " -Wfloat-conversion -Wsign-conversion"
  " -Wshadow -Wduplicated-cond"
  " -Wduplicated-branches -Wlogical-op"
  " -Wnull-dereference -Wuseless-cast"
  " -Wformat=2 -Wformat-security")

set(BUILD_SHARED_LIBS OFF)
set(BUILD_TESTING OFF)

add_subdirectory("deps/fmt-10.1.0")

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SUPPORT_MODULE_RTEXTURES OFF)
set(SUPPORT_MODULE_RAUDIO OFF)
set(SUPPORT_MODULE_RTEXT OFF)
set(SUPPORT_MODULE_RMODELS OFF)
add_subdirectory("deps/raylib-5.0")

add_executable(ticpp
  src/main.cpp
  src/tetris.cpp)
target_link_libraries(ticpp
  fmt
  raylib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Copy root/build/compile_commands.json to the root directory of the project
if (EXISTS "${CMAKE_BINARY_DIR}/compile_commands.json")
  FILE(COPY ${CMAKE_BINARY_DIR}/compile_commands.json DESTINATION ${CMAKE_HOME_DIRECTORY})
endif()
