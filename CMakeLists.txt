cmake_minimum_required(VERSION 3.22)
project(Turn_Based_Dungeon_v02)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(libs)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

set(CMAKE_CXX_STANDARD 17)

add_executable(Turn_Based_Dungeon_v02 ${SOURCES} src/Engine.cpp src/Engine.h src/Settings.h)
target_link_libraries(Turn_Based_Dungeon_v02 ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})