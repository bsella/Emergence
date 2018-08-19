cmake_minimum_required(VERSION 3.0.0)
project(Logic)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC")
qt5_add_resources(QRC logic.qrc)
add_custom_target(logic_qrc DEPENDS ${QRC})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_PATH})

include_directories(${MAIN_SRC_DIR} ${Qt5Widgets_INCLUDE_DIRS})

add_library(Logic SHARED LogicPlugin.cpp LogicPlugin.h)
add_library(lib_logic LogicNode.cpp LogicPlugin.h)

target_link_libraries(Logic lib_logic lib_data_t ${QRC})
add_dependencies(Logic logic_qrc)
