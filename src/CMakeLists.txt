cmake_minimum_required(VERSION 3.0.0)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB FORMS *.ui)
qt5_wrap_ui(UI_HEADERS ${FORMS})
qt5_add_resources(QRC src.qrc)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC")

include_directories(${MAIN_SRC_DIR} ${BIN_SRC_DIR} ${Qt5Widgets_INCLUDE_DIRS})

add_library(data_t data_t.cpp data_t.h)

add_library(core
	mainwindow.cpp
	Node.cpp
	NodeBox.cpp
	Workspace.cpp
	PluginManager.cpp
	mainwindow.h
	Node.h
	NodeBox.h
	Workspace.h
	signalManager.h
	${UI_HEADERS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)
add_executable(${PROJECT_NAME} main.cpp ${QRC})

target_link_libraries(${PROJECT_NAME} data_t core Qt5::Widgets)
