cmake_minimum_required(VERSION 3.0.0)
project(Compare)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC")
qt5_add_resources(QRC comp.qrc)
add_custom_target(compare_qrc DEPENDS ${QRC})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_PATH})

include_directories(${MAIN_SRC_DIR} ${Qt5Widgets_INCLUDE_DIRS})

add_library(Compare SHARED ComparePlugin.cpp ComparePlugin.h)
add_library(lib_compare
	CompNode.cpp
	CompNode.h)

target_link_libraries(Compare lib_compare lib_data_t ${QRC})
add_dependencies(Compare compare_qrc)
