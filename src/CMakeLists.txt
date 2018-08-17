cmake_minimum_required(VERSION 3.0.0)

find_package(Qt5Core    REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui     REQUIRED)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)
file(GLOB FORMS *.ui)
file(GLOB RESOURCES src.qrc)
qt5_wrap_ui(UI_HEADERS ${FORMS})

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC")

include_directories(${MAIN_SRC_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${Qt5Widgets_INCLUDE_DIRS})

add_library(libs ${SOURCES} ${HEADERS} ${UI_HEADERS} ${RESOURCES})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} libs Qt5::Widgets)
