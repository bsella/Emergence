cmake_minimum_required(VERSION 3.0.0)
project(LUT)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_PATH})

include_directories(. ${MAIN_SRC_DIR} ${Qt5Widgets_INCLUDE_DIRS})

add_library(LUT SHARED LUTPlugin.cpp LUTPlugin.h)
add_library(lut_lib PaletteNode.cpp Palette.cpp PaletteNode.h Palette.h)

target_link_libraries(LUT lut_lib)
