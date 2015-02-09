cmake_minimum_required( VERSION 2.8 )
set( CMAKE_BUILD_TYPE Release )

# Project info
project( m2g )
set( LIBRARY_NAME ${PROJECT_NAME} )
set( PROJECT_VERSION_MAJOR 0 )
set( PROJECT_VERSION_MINOR 2 )
set( PROJECT_VERSION_PATCH 1 )
set( PROJECT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH} )

# Compilation flags
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors" )

# Common libraries
include( FindPkgConfig )
pkg_search_module( SDL2 REQUIRED sdl2 )
pkg_search_module( SDL2IMAGE REQUIRED SDL2_image>=2.0.0 )
include_directories( ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} )
set( LIBRARIES "${SDL2IMAGE_LIBRARIES};${SDL2_LIBRARIES}" )
set( LIBRARIES "${LIBRARIES};tinyxml2" )

add_subdirectory( lib )
add_subdirectory( samples )
add_subdirectory( tests )

# TODO: Build samples' dependencies automatically.

include_directories( ${SOURCE_DIR} )
