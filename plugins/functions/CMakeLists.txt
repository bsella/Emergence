cmake_minimum_required(VERSION 3.0.0)
project(FunctionsPlugin)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC")
qt5_add_resources(QRC func.qrc)
add_custom_target(func_qrc DEPENDS ${QRC})

qt5_wrap_ui(UI_HEADERS functionmanager.ui)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_PATH})

include_directories(${MAIN_SRC_DIR} ${BIN_SRC_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${Qt5Widgets_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED FunctionPlugin.cpp FunctionPlugin.h)
add_library(func
	FunctionNode.cpp
	Function.cpp
	FunctionManager.cpp
	FunctionNode.h
	Function.h
	FunctionManager.h
	fromToStream.cpp
	${UI_HEADERS})

target_link_libraries(${PROJECT_NAME} func data_t ${QRC})
add_dependencies(${PROJECT_NAME} func_qrc)
