set( TESTS_SOURCE_DIR "${PROJECT_SOURCE_DIR}/../src/tests" )
set( LIBRARY_PATH ${PROJECT_SOURCE_DIR}/lib/libm2g.so )
include_directories( ${TESTS_SOURCE_DIR} )

# TODO: Create a function that lists all the source files in
# ${TESTS_SOURCE_DIR} and pass it to add_executable.
add_executable( samples "${TESTS_SOURCE_DIR}/m2g.cpp" )
