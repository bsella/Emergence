cmake_minimum_required(VERSION 3.0.0)
project(ColorPlugin)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC")
qt5_add_resources(QRC color.qrc)
add_custom_target(color_qrc DEPENDS ${QRC})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_PATH})

include_directories(${MAIN_SRC_DIR} ${Qt5Widgets_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED ColorPlugin.cpp ColorPlugin.h)
add_library(color
	ColorNode.cpp
	ColorNode.h)

target_link_libraries(${PROJECT_NAME} color data_t ${QRC})
add_dependencies(${PROJECT_NAME} color_qrc)
