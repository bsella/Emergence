cmake_minimum_required(VERSION 3.0.0)
project(IOPlugin)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC")
qt5_add_resources(QRC io.qrc)
add_custom_target(io_qrc DEPENDS ${QRC})

qt5_wrap_ui(UI_HEADERS exportimagedialog.ui)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_PATH})

include_directories(${MAIN_SRC_DIR} ${BIN_SRC_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${Qt5Widgets_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED IoPlugin.cpp IoPlugin.h)
add_library(io
	InputNode.cpp
	OutputNode.cpp
	ExportImageDialog.cpp
	InputNode.h
	OutputNode.h
	ExportImageDialog.h
	${UI_HEADERS})

target_link_libraries(${PROJECT_NAME} io data_t ${QRC})
add_dependencies(${PROJECT_NAME} io_qrc)
