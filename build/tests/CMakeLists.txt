set( TESTS_SOURCE_DIR "${PROJECT_SOURCE_DIR}/../src/tests" )
set( LIBRARY_PATH ${PROJECT_SOURCE_DIR}/lib/libm2g.so )
include_directories( ${TESTS_SOURCE_DIR} )

set( MOCKS_FILES "${TESTS_SOURCE_DIR}/mocks/mock_tileset.hpp" )
add_executable(
    tests
    "${TESTS_SOURCE_DIR}/main.cpp"
    "${TESTS_SOURCE_DIR}/drawables/tileset.cpp"
    "${TESTS_SOURCE_DIR}/drawables/tile_sprite.cpp"
    "${TESTS_SOURCE_DIR}/drawables/animation_state.cpp"
    "${TESTS_SOURCE_DIR}/drawables/animation_data.cpp"
    "${TESTS_SOURCE_DIR}/drawables/animation.cpp"
    "${TESTS_SOURCE_DIR}/graphics_library.cpp"
    "${MOCKS_FILES}" )
add_dependencies( tests ${LIBRARY_NAME} )
target_link_libraries( tests ${LIBRARY_PATH};-lgmock;-pthread;${LIBRARIES} )
