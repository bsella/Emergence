cmake_minimum_required(VERSION 3.0.0)
project(Logic)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC")
#qt5_add_resources(QRC logic.qrc)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_PATH})

include_directories(${MAIN_SRC_DIR} ${Qt5Widgets_INCLUDE_DIRS})

add_library(Logic SHARED LogicPlugin.cpp LogicPlugin.h)
add_library(logic_lib LogicNode.cpp LogicPlugin.h)

target_link_libraries(Logic logic_lib ${QRC})
