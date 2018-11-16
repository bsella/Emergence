cmake_minimum_required(VERSION 3.0.0)
project(MathPlugin)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC")
qt5_add_resources(QRC math.qrc)
add_custom_target(math_qrc DEPENDS ${QRC})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_PATH})

include_directories(${MAIN_SRC_DIR} ${BIN_SRC_DIR} ${Qt5Widgets_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED MathPlugin.cpp MathPlugin.h)
add_library(math
	MathNode.cpp
	RealNode.cpp
	ComplexNode.cpp
	MathNode.h
	RealNode.h
	fromToStream.cpp
	ComplexNode.h)

target_link_libraries(${PROJECT_NAME} math data_t ${QRC})
add_dependencies(${PROJECT_NAME} math_qrc)
