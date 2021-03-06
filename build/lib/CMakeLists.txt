set( SOURCE_DIR "${PROJECT_SOURCE_DIR}/../src" )

set(
    SOURCE_FILES
    #"${SOURCE_DIR}/utilities/alignment.cpp"
    #"${SOURCE_DIR}/utilities/rect.cpp"
    #"${SOURCE_DIR}/drawables/drawable.cpp"
    #"${SOURCE_DIR}/drawables/drawables_set.cpp"
    "${SOURCE_DIR}/drawables/tileset.cpp"
    #"${SOURCE_DIR}/drawables/collidable.cpp"
    "${SOURCE_DIR}/drawables/tile_sprite.cpp"
    "${SOURCE_DIR}/drawables/animation_state.cpp"
    "${SOURCE_DIR}/drawables/animation_data.cpp"
    "${SOURCE_DIR}/drawables/animation.cpp"
    "${SOURCE_DIR}/graphics_library.cpp"
    #"${SOURCE_DIR}/m2g.cpp"
)
set(
    HEADER_FILES
    #"${SOURCE_DIR}/utilities/alignment.hpp"
    #"${SOURCE_DIR}/utilities/rect.hpp"
    #"${SOURCE_DIR}/drawables/drawable.hpp"
    #"${SOURCE_DIR}/drawables/drawables_set.hpp"
    "${SOURCE_DIR}/drawables/tileset.hpp"
    #"${SOURCE_DIR}/drawables/collidable.hpp"
    "${SOURCE_DIR}/drawables/tile_sprite.hpp"
    "${SOURCE_DIR}/drawables/animation_state.hpp"
    "${SOURCE_DIR}/drawables/animation_data.hpp"
    "${SOURCE_DIR}/drawables/animation.hpp"
    "${SOURCE_DIR}/graphics_library.hpp"
    #"${SOURCE_DIR}/m2g.hpp"
)

# Build the library.
if( BUILD_STATIC_M2G )
    add_library( ${LIBRARY_NAME} STATIC ${SOURCE_FILES} )
else( BUILD_STATIC_M2G )
    add_library( ${LIBRARY_NAME} SHARED ${SOURCE_FILES} )
endif( BUILD_STATIC_M2G )
set_target_properties(
    ${LIBRARY_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION_STRING}
    SOVERSION ${PROJECT_VERSION_MAJOR} )

# Instalation.
foreach( header_file ${HEADER_FILES})
    string(
        REGEX REPLACE ".*/([^/]*.hpp)" "\\1"
        header_filename
        ${header_file}
    )
    message( "header_filename: [${header_filename}]" )
    install( DIRECTORY "${SOURCE_DIR}/" DESTINATION include/m2g FILES_MATCHING PATTERN "${header_filename}" )
endforeach( header_file )
install( TARGETS ${LIBRARY_NAME} DESTINATION lib )

# Uninstall target
# Source: http://www.cmake.org/Wiki/CMake_FAQ#Can_I_do_.22make_uninstall.22_with_CMake.3F
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(
    uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake )
