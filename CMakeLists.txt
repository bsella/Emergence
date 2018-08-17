cmake_minimum_required(VERSION 3.0.0)

project(Emergence)

if ( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE Release)
endif()

set(PLUGIN_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(MAIN_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(src)
add_subdirectory(plugins)
