cmake_minimum_required(VERSION 3.0.0)
project(Color)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_PATH})

include_directories(${MAIN_SRC_DIR} ${Qt5Widgets_INCLUDE_DIRS})

add_library(Color SHARED ColorPlugin.cpp ColorPlugin.h)
add_library(lib_color
	ColorNode.cpp
	ColorNode.h)

target_link_libraries(Color lib_color lib_data_t)
