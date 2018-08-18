cmake_minimum_required(VERSION 3.0.0)
project(Io)

find_package(Qt5Core    REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui     REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC")
#qt5_add_resources(QRC io.qrc)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_PATH})

include_directories(${MAIN_SRC_DIR} ${Qt5Widgets_INCLUDE_DIRS})

add_library(Io SHARED IoPlugin.cpp IoPlugin.h)
add_library(io_lib InputNode.cpp OutputNode.cpp InputNode.h OutputNode.h)

target_link_libraries(Io io_lib core)
