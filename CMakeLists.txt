cmake_minimum_required( VERSION 2.8 )
set( CMAKE_BUILD_TYPE Release )

# Project info
project( m2g )
set( LIBRARY_NAME ${PROJECT_NAME} )
set( PROJECT_VERSION_MAJOR 0 )
set( PROJECT_VERSION_MINOR 1 )
set( PROJECT_VERSION_PATCH 0 )
set( PROJECT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH} )

# Project files
#file( GLOB_RECURSE SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp" ) # TODO: Remove sample and test files.
#list( REMOVE_ITEM SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/tests/main.cpp" )
set(
    SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/src/drawables/drawable.cpp"
    "${PROJECT_SOURCE_DIR}/src/drawables/tileset.cpp"
    "${PROJECT_SOURCE_DIR}/src/drawables/collidable.cpp"
    "${PROJECT_SOURCE_DIR}/src/drawables/sprite.cpp"
    "${PROJECT_SOURCE_DIR}/src/drawables/animation_data.cpp"
    "${PROJECT_SOURCE_DIR}/src/drawables/animation.cpp"
)

include_directories( "${PROJECT_SOURCE_DIR}/src" )

# Compiler flags
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic-errors" )

# Include libraries SDL2, SDL2_image and SDL2_ttf
include( FindPkgConfig )
pkg_search_module( SDL2 REQUIRED sdl2 )
pkg_search_module( SDL2IMAGE REQUIRED SDL2_image>=2.0.0 )
pkg_search_module( SDL2TTF REQUIRED SDL2_ttf>=2.0.0 )
include_directories( ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} )
set( LIBRARIES "${LIBRARIES};${SDL2IMAGE_LIBRARIES};${SDL2TTF_LIBRARIES};${SDL2_LIBRARIES}" )

# Include library OpenGL.
find_package( OpenGL REQUIRED )
include_directories( ${OPENGL_INCLUDE_DIR} )
set( LIBRARIES "${LIBRARIES};${OPENGL_LIBRARIES}" )

# Include library tinyxml2
set( LIBRARIES "${LIBRARIES};-ltinyxml2" )

# Configure header file
#configure_file(
#    "${PROJECT_SOURCE_DIR}/src/shader_loader.hpp.in"
#    "${PROJECT_BINARY_DIR}/src/shader_loader.hpp" )

# Build shared library.
add_library( ${LIBRARY_NAME} SHARED ${SOURCE_FILES} )
set_target_properties(
    ${LIBRARY_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION_STRING}
    SOVERSION ${PROJECT_VERSION_MAJOR} )

# Build samples
#set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/samples/gui ) # TODO: Does this affect the target instalation?
#set( SAMPLE_KERNEL_SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/samples/kernel/sample_app.cpp" )
#message( "SAMPLE_KERNEL_SOURCE_FILES: ${SAMPLE_KERNEL_SOURCE_FILES}" )
#add_executable(
#    gui-buttons
#    ${PROJECT_SOURCE_DIR}/src/samples/gui/buttons/buttons.cpp ${SAMPLE_KERNEL_SOURCE_FILES} )
#add_dependencies( gui-buttons ${LIBRARY_NAME} )
#target_link_libraries( gui-buttons "-L${CMAKE_SOURCE_DIR}" "${LIBRARIES}" "-lm2g" ) # TODO: Or use the previous ${LIBRARY_NAME} library?
# TODO: Add old sample "particles systems".

# Link libraries.
#target_link_libraries( ${LIBRARY_NAME} ${LIBRARIES} )

# Instalation.
install( DIRECTORY src/ DESTINATION include/m2g FILES_MATCHING PATTERN "*.hpp" )
install( TARGETS ${LIBRARY_NAME} DESTINATION lib )
# TODO: Install samples.

# Uninstall target
# Source: http://www.cmake.org/Wiki/CMake_FAQ#Can_I_do_.22make_uninstall.22_with_CMake.3F
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(
    uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake )
