cmake_minimum_required(VERSION 3.0.0)
project(Math)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC")
qt5_add_resources(QRC math.qrc)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_PATH})

include_directories(. ${MAIN_SRC_DIR} ${Qt5Widgets_INCLUDE_DIRS})

add_library(Math SHARED MathPlugin.cpp MathPlugin.h)
add_library(math_lib
	MathNode.cpp
	RealNode.cpp
	ComplexNode.cpp
	MathNode.h
	RealNode.h
	ComplexNode.h
	${MAIN_SRC_DIR}/data_t.cpp
	${MAIN_SRC_DIR}/data_t.h
	)

target_link_libraries(Math math_lib ${QRC})
