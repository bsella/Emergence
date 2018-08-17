cmake_minimum_required(VERSION 3.0.0)
project(Logic)

find_package(Qt5Core    REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui     REQUIRED)

file(GLOB PLUGIN_SOURCES LogicPlugin.cpp)
file(GLOB PLUGIN_HEADERS LogicPlugin.h)
file(GLOB SOURCES LogicNode.cpp)
file(GLOB HEADERS LogicNode.h)

set(CMAKE_AUTOMOC ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_PATH} )
set(Qt5_LIBRARIES ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5Gui_LIBRARIES})

include_directories(${MAIN_SRC_DIR} ${Qt5Widgets_INCLUDE_DIRS})

add_library(Logic SHARED ${PLUGIN_SOURCES} ${PLUGIN_HEADERS})
