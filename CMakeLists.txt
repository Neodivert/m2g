cmake_minimum_required( VERSION 2.8 )
set( CMAKE_BUILD_TYPE Release )

# Project info
project( m2g )
set( LIBRARY_NAME ${PROJECT_NAME} )
set( PROJECT_VERSION_MAJOR 0 )
set( PROJECT_VERSION_MINOR 3 )
set( PROJECT_VERSION_PATCH 0 )
set( PROJECT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH} )

# Compilation flags
if(CMAKE_COMPILER_IS_GNUCXX)
	message(STATUS "GCC detected, adding compile flags")
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors" )
endif(CMAKE_COMPILER_IS_GNUCXX)


# Common libraries
include( FindPkgConfig )
set( LIBRARIES "${LIBRARIES};tinyxml2" )
set( LIBRARIES "${LIBRARIES};sfml-graphics;sfml-window;sfml-audio;sfml-system" )

include_directories( ${CMAKE_SOURCE_DIR}/include )

add_subdirectory( lib )

if( TESTS )
    add_subdirectory( tests )
endif()

