set( TESTS_SOURCE_DIR "${PROJECT_SOURCE_DIR}/../src/tests" )
set( LIBRARY_PATH ${PROJECT_SOURCE_DIR}/lib/libm2g.so )
include_directories( ${TESTS_SOURCE_DIR} )

# TODO: Create a function that lists all the source files in
# ${TESTS_SOURCE_DIR} and pass it to add_executable.
add_executable(
    tests
    "${TESTS_SOURCE_DIR}/main.cpp"
    "${TESTS_SOURCE_DIR}/drawables/tileset.cpp"
    "${TESTS_SOURCE_DIR}/drawables/tile_sprite.cpp" )
add_dependencies( tests ${LIBRARY_NAME} )
target_link_libraries( tests ${LIBRARY_PATH};-lgmock;-pthread;${LIBRARIES} )
