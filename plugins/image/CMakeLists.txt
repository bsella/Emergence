cmake_minimum_required(VERSION 3.0.0)
project(Image)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC")
qt5_add_resources(QRC image.qrc)
add_custom_target(image_qrc DEPENDS ${QRC})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_PATH})

include_directories(${MAIN_SRC_DIR} ${Qt5Widgets_INCLUDE_DIRS})

add_library(Image SHARED ImagePlugin.cpp ImagePlugin.h)
add_library(lib_image
	BitmapNode.cpp
	BitmapNode.h)

target_link_libraries(Image lib_image lib_data_t ${QRC})
add_dependencies(Image image_qrc)
