cmake_minimum_required(VERSION 3.0.0)
project(Condition)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC")
qt5_add_resources(QRC cond.qrc)
add_custom_target(cond_qrc DEPENDS ${QRC})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_PATH})

include_directories(${MAIN_SRC_DIR} ${Qt5Widgets_INCLUDE_DIRS})

add_library(Condition SHARED ConditionPlugin.cpp ConditionPlugin.h)
add_library(lib_cond
	IfNode.cpp
	IfNode.h)

target_link_libraries(Condition lib_cond lib_data_t ${QRC})
add_dependencies(Condition cond_qrc)
