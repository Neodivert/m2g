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
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors" )

# Common libraries
include( FindPkgConfig )
set( LIBRARIES "${LIBRARIES};tinyxml2" )

# Detect and add SFML (FIXME: This will work only on GNU/Linux.)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/usr/share/SFML/cmake/Modules/")
find_package(SFML 2 REQUIRED system window graphics )
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    set( LIBRARIES "${LIBRARIES};${SFML_LIBRARIES}" )
endif()

add_subdirectory( lib )
add_subdirectory( tests )

include_directories( ${SOURCE_DIR} )
