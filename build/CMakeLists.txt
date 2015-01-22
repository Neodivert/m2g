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

add_subdirectory( lib )
