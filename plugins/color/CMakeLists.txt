cmake_minimum_required(VERSION 3.0.0)
project(Color)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_PATH})

include_directories(${MAIN_SRC_DIR} ${Qt5Widgets_INCLUDE_DIRS})

add_library(Color SHARED ColorPlugin.cpp ColorPlugin.h)
add_library(color_lib
	ColorNode.cpp
	ColorNode.h
	${MAIN_SRC_DIR}/data_t.cpp
	${MAIN_SRC_DIR}/data_t.h
	)

target_link_libraries(Color color_lib)
