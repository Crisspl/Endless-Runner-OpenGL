cmake_minimum_required(VERSION 2.8)

project(FHL)

set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake-modules/")

option(FHL_BUILD_ENDLESS_RUNNER "Decides to build an example game or not (if so extra dependencies are needed)" OFF)

add_subdirectory("FHL/")

if(FHL_BUILD_ENDLESS_RUNNER)
	add_subdirectory("EndlessRunner/")
endif()